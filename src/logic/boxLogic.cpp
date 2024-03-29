#include <algorithm>
#include "boxLogic.h"
#include <unistd.h>
#include <time.h>
#include "car.h"
#include "../src/game_entities/room.h"
#include <iostream>
#include "../src/constants/b2DVars.h"
#include <string>
#include "../src/configuration/yaml_configuration.h"



BoxLogic::BoxLogic(int requiredPlayers):
    isActive(true),
    configuration(YamlConfiguration().ReadServerConfiguration()),
    game(requiredPlayers, configuration.getGameTime(), configuration.getResponsesPerSec()),
    cars(),
    ballPunchesLocal(),
    ballPunchesVisitor(),
    contactListener(cars, ballPunchesLocal, ballPunchesVisitor) {
    world = std::make_unique<b2World>(b2Vec2(0.0f,
                                             configuration.getMapGravity()));
    world->SetContactListener(&this->contactListener);
    createWalls();
    createBall();
    createSoccerGoals();
}

void BoxLogic::createSoccerGoals() {
    float roof_x = 0.0f;
    float roof_y = 0.0f;

    b2BodyDef roof;
    roof.type = b2_staticBody;
    roof.position.Set(roof_x, roof_y);
    roof.angle = 0;

        soccerGoals.emplace_back(SoccerGoal(this->world->CreateBody(&roof),
                                            this->world->CreateBody(&roof)));
        soccerGoals.emplace_back(SoccerGoal(this->world->CreateBody(&roof),
                                            this->world->CreateBody(&roof)));

    b2FixtureDef edgeFixtureDef;
    b2EdgeShape edge;
    float roofXStart[] = {-4.0f, 4.0f};
    float roofXEnd[] = {-3.3f, 3.3f};
    float roofYStart[] = {0.0f, 0.0f};
    float roofYEnd[] = {0.0f, 0.0f};

    int i = 0;
    for (auto &x : soccerGoals) {
        edge.SetTwoSided(b2Vec2(roofXStart[i], roofYStart[i]),
                         b2Vec2(roofXEnd[i], roofYEnd[i]));
        edgeFixtureDef.shape = &edge;
        edgeFixtureDef.filter.categoryBits = B2DVars().BIT_SOCCER_GOAL;
        x.createFixtureRoof(edgeFixtureDef);
        i++;
    }
    b2FixtureDef edgeFixtureDef2;
    float wallXStart[] = {-4.0f, 4.0f};
    float wallXEnd[] = {-3.6f, 3.6f};
    float wallYStart[] = {2.5f, 2.5f};
    float wallYEnd[] = {0.0f, 0.0f};
    i = 0;
    for (auto &x : soccerGoals) {
        edge.SetTwoSided(b2Vec2(wallXStart[i], wallYStart[i]),
                         b2Vec2(wallXEnd[i], wallYEnd[i]));
        edgeFixtureDef2.shape = &edge;
        edgeFixtureDef2.filter.categoryBits = B2DVars().BIT_SOCCER_GOAL;
        x.createFixtureWall(edgeFixtureDef2);
        i++;
    }
}

b2Vec2 BoxLogic::getGravity() {
    return this->world->GetGravity();
}

int BoxLogic::wallsAmount() {
    return this->walls.size();
}

void BoxLogic::updateTime() {
    float timeStep = 1.0f / configuration.getResponsesPerSec();
    world->Step(timeStep, LogicValues().VELOCITY_ITERATIONS,
                LogicValues().POSITION_ITERATIONS);
    usleep(timeStep*1000000);  // (unsleep utiliza microsegundos 1x10-6)
    game.updateTime();
}

bool BoxLogic::ballIsAwake() {
    return ball.isAwake();
}
void BoxLogic::createBall() {
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(LogicValues().POS_X_INITIAL_BALL, LogicValues().POS_Y_INITIAL_BALL);
    this->ball.setBody(world->CreateBody(&ballDef));
    this->ball.setForces(configuration.getForceFlipShot(), configuration.getForceRedShot(),
                         configuration.getForcePurpleShot(), configuration.getForceGoldShot());

    b2CircleShape shapeCircle;
    shapeCircle.m_radius = configuration.getBallRadius();

    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &shapeCircle;
    fixtureCircle.density = configuration.getBallDensity();
    fixtureCircle.friction = configuration.getBallFriction();
    fixtureCircle.restitution = configuration.getBallRestitution();
    fixtureCircle.filter.categoryBits = B2DVars().BIT_BALL;
    fixtureCircle.filter.maskBits = B2DVars().BIT_CAR |
                                    B2DVars().BIT_GROUND |
                                    B2DVars().BIT_SOCCER_GOAL;
    ball.createFixture(fixtureCircle);
    contactListener.addBall(&ball);
}

void BoxLogic::createCar(int id) {
    float wCar = configuration.getCarWidth();
    float hCar = configuration.getCarHeight();

    b2BodyDef carBodyDef;
    carBodyDef.type = b2_dynamicBody;
    carBodyDef.angle = LogicValues().ANGLE_CAR;
    if (id%2) {
        carBodyDef.position.Set(LogicValues().POS_X_INITIAL_CAR_LOCAL, LogicValues().POS_Y_INITIAL_CAR_LOCAL);
    } else {
        carBodyDef.position.Set(LogicValues().POS_X_INITIAL_CAR_VISITOR, LogicValues().POS_Y_INITIAL_CAR_VISITOR);
    }
    cars.emplace_back(Car(world->CreateBody(&carBodyDef), id, configuration.getTorqueForce()));
    b2PolygonShape dynamicCar;
    dynamicCar.SetAsBox(wCar/2.0f, hCar/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCar;
    fixtureDef.density = configuration.getCarDensity();
    fixtureDef.friction = configuration.getCarFriction();
    fixtureDef.restitution = configuration.getCarRestitution();
    fixtureDef.filter.categoryBits = B2DVars().BIT_CAR;
    fixtureDef.filter.maskBits = B2DVars().BIT_BALL |
                                 B2DVars().BIT_GROUND |
                                 B2DVars().BIT_SOCCER_GOAL;
    cars.back().createFixture(fixtureDef, 0);
    cars.back().setTurboForce(configuration.getTurboForce());

    // Creación 4 sensores
    b2FixtureDef sensorDef;
    dynamicCar.SetAsBox(wCar/2.0f, 0.1, b2Vec2(0, -hCar/2), 0);
    sensorDef.shape = &dynamicCar;
    sensorDef.filter.categoryBits = B2DVars().BIT_CAR;
    sensorDef.filter.maskBits = B2DVars().BIT_BALL |
                                B2DVars().BIT_GROUND |
                                B2DVars().BIT_SOCCER_GOAL;
    sensorDef.isSensor = true;
    cars.back().createFixture(sensorDef, LogicValues().TOP_SENSOR);

    dynamicCar.SetAsBox(wCar/2.0f, 0.1, b2Vec2(0, hCar/2), 0);
    sensorDef.shape = &dynamicCar;
    cars.back().createFixture(sensorDef, LogicValues().DOWN_SENSOR);

    dynamicCar.SetAsBox(0.1, hCar/2.0f, b2Vec2(wCar/2, 0), 0);
    sensorDef.shape = &dynamicCar;
    if(id%2)
        cars.back().createFixture(sensorDef, LogicValues().HEAD_SENSOR);
    else
        cars.back().createFixture(sensorDef, LogicValues().TAIL_SENSOR);

    dynamicCar.SetAsBox(0.1, hCar/2.0f, b2Vec2(-wCar/2, 0), 0);
    sensorDef.shape = &dynamicCar;

    if(id%2)
        cars.back().createFixture(sensorDef, LogicValues().TAIL_SENSOR);
    else
        cars.back().createFixture(sensorDef, LogicValues().HEAD_SENSOR);
}

void BoxLogic::createWalls() {
    float ground_x = 0.0f;
    float ground_y = 0.0f;

    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(ground_x, ground_y);
    groundDef.angle = LogicValues().ANGLE_BALL;
    for (int i = 0; i < 4; i++) {
        walls.emplace_back(this->world->CreateBody(&groundDef));
    }
    b2FixtureDef edgeFixtureDef;
    b2EdgeShape edge;
    float edgesXStart[] = {-4.0f, -4.0f, 4.0f, -4.0f};
    float edgesXEnd[] = {4.0f, -4.0f, 4.0f, 4.0f};
    float edgesYStart[] = {2.5f, -3.0f, -3.0f, -3.0f};
    float edgesYEnd[] = {2.5f, 3.0f, 3.0f, -3.0f};

    int i = 0;
    for (auto &x : walls) {
        edge.SetTwoSided(b2Vec2(edgesXStart[i], edgesYStart[i]),
                         b2Vec2(edgesXEnd[i], edgesYEnd[i]));
        edgeFixtureDef.shape = &edge;
        edgeFixtureDef.filter.categoryBits = B2DVars().BIT_GROUND;
        edgeFixtureDef.filter.maskBits = B2DVars().BIT_BALL | B2DVars().BIT_CAR;
        x->CreateFixture(&edgeFixtureDef);
        i++;
    }
}

void BoxLogic::addPlayer(int id) {
    this->createCar(id);
}

BoxLogic::~BoxLogic() {
}

float BoxLogic::getData(int key, const b2Body* body) {
    switch (key) {
        case 0:
            return body->GetPosition().x;
        case 1:
            return body->GetPosition().y;
    }
    return 0;
}

float BoxLogic::getBallData(int key) {
    switch (key) {
        case LogicValues().POS_X:
            return this->ball.getBallBody()->GetPosition().x;
        case LogicValues().POS_Y:
            return this->ball.getBallBody()->GetPosition().y;
        case LogicValues().X_VELOCITY:
            return this->ball.getBallBody()->GetLinearVelocity().x;
        case LogicValues().Y_VELOCITY:
            return this->ball.getBallBody()->GetLinearVelocity().y;
        case LogicValues().ANGLE:
            return this->ball.getBallBody()->GetAngle();
    }
    return 0.0f;
}

int BoxLogic::playersAmount() {
    return this->cars.size();
}

float BoxLogic::getCarData(int carNumber, int key) {
    auto car = getCar(carNumber);
    if (car != nullptr) {
        return car->getData(key);
    }
    return -1;
}

Car* BoxLogic::getCar(int carID) {
    auto found = std::find_if(this->cars.begin(),
                 this->cars.end(),
                 [&carID](Car &car){return car.getId() == carID;});

    if (found != this->cars.end()) {
        return found.base();
    }
    return nullptr;
}

b2Vec2 BoxLogic::getVectorForce(int direction, directions& lastDir) {
    if (direction == LogicValues().LEFT_DIRECTION) {
        lastDir = LEFT_LAST_DIRECTION;
        return b2Vec2(configuration.getMovementForceModule()*(-1), 0.0f);
    } else if (direction == LogicValues().RIGHT_DIRECTION) {
        lastDir = RIGHT_LAST_DIRECTION;
        return(b2Vec2(configuration.getMovementForceModule(), 0.0f));
    } else if (direction == LogicValues().UP_DIRECTION) {
        return (b2Vec2(0.0f, configuration.getJumpImpulse()*(-1)));
    }
    return (b2Vec2(0.0f, configuration.getJumpImpulse()*(-1)));
}

void BoxLogic::startMove(int carNumber, bool direction) {
    directions lastDir = NONE;
    b2Vec2 vel = getVectorForce((int)direction, lastDir);
    getCar(carNumber)->startMove(vel);
    getCar(carNumber)->changeLastDirection(lastDir);
}

void BoxLogic::stopMove(int carNumber) {
    getCar(carNumber)->stopMove();
}

void BoxLogic::jump(int carNumber) {
    directions lastDirDummy = NONE;
    b2Vec2 vel = getVectorForce((LogicValues().UP_DIRECTION), lastDirDummy);
    getCar(carNumber)->jump(vel);
}

PlayerResponses BoxLogic::getPlayersData() {
    std::vector<PlayerResponse> vector;

    for (auto &x : cars) {
        // cppcheck-suppress useStlAlgorithm
        vector.emplace_back(x.getId(), x.getData(LogicValues().POS_X),
                            x.getData(LogicValues().POS_Y),
                            x.getData(LogicValues().ANGLE),
                            ((x.getData(LogicValues().X_VELOCITY) != 0) ||
                            (x.getData(LogicValues().Y_VELOCITY) != 0)),
                            (x.isJumping()),
                            x.getData(LogicValues().USING_TURBO),
                            x.getHasPunchedTheBall(),
                            x.getData(LogicValues().ACCELERATING),
                            x.isLocal(),
                            x.getGoals(), x.getAssists(), x.getSaves(),
                            x.isFacingLeft(), x.remainingTurbo());
    }
    return PlayerResponses(vector);
}


void BoxLogic::updateStatus() {
    verifyDoubleJump();
    verifyTurbo();
    verifyGoal();
    verifyAcceleration();
    verifyFlip();
    verifyPunch();
}

void BoxLogic::verifyAcceleration() {
    for (auto &x : cars) {
        x.verifyAcceleration();
    }
}

void BoxLogic::verifyGoal() {
    this->updateGoal();
    this->resetPositions();
}


void BoxLogic::verifyDoubleJump() {
    for (auto &x : cars) {
        x.verifyDoubleJump();
    }
}

void BoxLogic::verifyTurbo() {
    for (auto &x : cars) {
        x.verifyTurbo();
    }
}

void BoxLogic::verifyFlip() {
    for (auto &x : cars) {
        x.verifyFlip();
        contactListener.verifyFlip(x);
    }
}

void BoxLogic::applyTurbo(int carNumber) {
    getCar(carNumber)->applyTurbo();
}

/*
 * teamGoal = 0 -> No hay goles
 * teamGoal = 1 -> Gol Local
 * teamGoal = 2 -> Gol visitante
 */
void BoxLogic::updateGoal() {  // refactor -> crear objeto pelota.
    int teamGoal = 0;

    if ((getData(LogicValues().POS_X, ball.getBallBody()) > 3.3) &&
        ((getData(LogicValues().POS_Y, ball.getBallBody())) > 0)) {
        teamGoal = 2;
        if (!this->ballPunchesVisitor.empty()) {
            int goalerId = this->ballPunchesVisitor.back();
            this->addGoalToPlayer(goalerId);
            if (this->ballPunchesVisitor.size() > 1) {
                auto found_assistant = std::find_if(this->cars.rbegin(),
                                                    this->cars.rend(),
                                                    [&goalerId](Car &car)
                                                    {return car.getId() != goalerId;});
                if (found_assistant != this->cars.rend() &&
                    !found_assistant->isLocal()) {
                    found_assistant->addAssist();
                }
            }
            this->ballPunchesVisitor.clear();
        }
    } else if ((getData(LogicValues().POS_X, ball.getBallBody()) < (-3.3))
                && ((getData(LogicValues().POS_Y, ball.getBallBody())) > 0)) {
        teamGoal = 1;
        if (!this->ballPunchesLocal.empty()) {
            int goalerId = this->ballPunchesLocal.back();
            this->addGoalToPlayer(goalerId);
            if (this->ballPunchesLocal.size() > 1) {
                auto found_assistant = std::find_if(this->cars.rbegin(),
                                                    this->cars.rend(),
                                                    [&goalerId](Car &car)
                                                    {return car.getId() != goalerId;});
                if (found_assistant != this->cars.rend() && found_assistant->isLocal()) {
                    found_assistant->addAssist();
                }
            }
            this->ballPunchesLocal.clear();
        }
    }
    game.updateGame(teamGoal);
}
bool BoxLogic::matchFinished() {
    return game.matchFinished();
}
void BoxLogic::resetPositions() {
    if (game.goal()) {
        for (auto &x : cars) {
            x.resetPosition();
        }
        ball.getBallBody()->SetLinearVelocity(b2Vec2(0.0f, 0.1f));
        ball.getBallBody()->SetTransform(b2Vec2(LogicValues().POS_X_INITIAL_BALL, LogicValues().POS_Y_INITIAL_BALL), 0);
        ball.getBallBody()->SetAngularVelocity(0);
        ball.resetPunch();
    }
}

int BoxLogic::getTime() {
    return game.getTime();
}

MatchResponse BoxLogic::gameData(BallResponse &ball, PlayerResponses &players) {
    return (game.response(ball, players));
}

void BoxLogic::resetData() {
    game.resetData();
}

void BoxLogic::removePlayer(int id) {
    auto found = std::remove_if(this->cars.begin(),
                                this->cars.end(),
                                [&id](Car &car){return car.getId() == id;});
    found->destroy(this->world);
    this->cars.erase(found, this->cars.end());
}

bool BoxLogic::isGoal() {
    return this->game.goal();
}
void BoxLogic::setRoomInfo(Room &room, bool replay) {
    game.setStatus(room, replay);
}

void BoxLogic::addGoalToPlayer(int id) {
    auto found = std::find_if(this->cars.begin(),
                 this->cars.end(),
                 [&id](Car &car)
                 {return car.getId() == id;});

    if (found != this->cars.end()) {
        found->addGoal();
    }
}

void BoxLogic::addAssistToPlayer(int id) {
    auto found = std::find_if(this->cars.begin(),
                              this->cars.end(),
                              [&id](Car &car)
                              {return car.getId() == id;});

    if (found != this->cars.end()) {
        found->addAssist();
    }
}

void BoxLogic::updateLastDirection(int id,
                                   const std::basic_string<char>& deserializedCommand) {
    directions lastDir = NONE;
    if (deserializedCommand == CommandValues().DESERIALIZED_UP_PUSHED)
        lastDir = UP_LAST_DIRECTION;
    else if (deserializedCommand == CommandValues().DESERIALIZED_DOWN_PUSHED)
        lastDir = DOWN_LAST_DIRECTION;

    getCar(id)->changeLastDirection(lastDir);
}

void BoxLogic::verifyPunch() {
    ball.verifyPunch();
    for (auto &x : cars) {
        x.verifyPunch();
    }
}

bool BoxLogic::getBallDataPunched(const int key) {
    switch (key) {
        case LogicValues().HAS_BEEN_PUNCHED_NORMAL:
            return (ball.isWasPunchedNormal());
        case LogicValues().HAS_BEEN_PUNCHED_FLIP_SHOT:
            return (ball.isWasPunchedFlipShot());
        case LogicValues().HAS_BEEN_PUNCHED_RED_SHOT:
            return (ball.isWasPunchedRedShot());
        case LogicValues().HAS_BEEN_PUNCHED_PURPLE_SHOT:
            return (ball.isWasPunchedPurpleShot());
        case LogicValues().HAS_BEEN_PUNCHED_GOLD_SHOT:
            return (ball.isWasPunchedGoldShot());
    }
    return false;
}