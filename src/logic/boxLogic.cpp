#include "boxLogic.h"
#include <unistd.h>
#include <time.h>
#include "car.h"
#include <iostream>

BoxLogic::BoxLogic():
    isActive(true) {
    world = std::make_unique<b2World>(b2Vec2(0.0f, 9.8f));
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

        soccerGoals.emplace_back(SoccerGoal(this->world->CreateBody(&roof), this->world->CreateBody(&roof)));
        soccerGoals.emplace_back(SoccerGoal(this->world->CreateBody(&roof), this->world->CreateBody(&roof)));

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
    float timeStep = 1.0f / 25.0f;
    world->Step(timeStep, LogicValues().VELOCITY_ITERATIONS,
                LogicValues().POSITION_ITERATIONS);
    usleep(timeStep*1000000);  // (unsleep utiliza microsegundos 1x10-6)
    game.updateTime();
}

bool BoxLogic::ballIsAwake() {
    return ball->IsAwake();
}
void BoxLogic::createBall() {
    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(0, -2.8f);
    this->ball = world->CreateBody(&ballDef);

    b2CircleShape shapeCircle;
    shapeCircle.m_radius = LogicValues().RADIUS_BALL;

    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &shapeCircle;
    fixtureCircle.density = LogicValues().DENSITY_BALL;
    fixtureCircle.friction = LogicValues().FRICTION_BALL;
    fixtureCircle.restitution = LogicValues().RESTITUTION_BALL;
    ball->CreateFixture(&fixtureCircle);
}

void BoxLogic::createCar(int id) {
    float wCar = LogicValues().W_CAR;
    float hCar = LogicValues().H_CAR;

    b2BodyDef carBodyDef;
    carBodyDef.type = b2_dynamicBody;
    carBodyDef.angle = LogicValues().ANGLE_CAR;
    carBodyDef.position.Set(2.0f, -2.0f);
    cars.emplace_back(Car(world->CreateBody(&carBodyDef), id));
    b2PolygonShape dynamicCar;
    dynamicCar.SetAsBox(wCar/2.0f, hCar/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCar;
    fixtureDef.density = LogicValues().DENSITY_CAR;
    fixtureDef.friction = LogicValues().FRICTION_CAR;
    fixtureDef.restitution = LogicValues().RESTITUTION_CAR;
    cars.back().createFixture(fixtureDef);
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
        x->CreateFixture(&edgeFixtureDef);
        i++;
    }
}

void BoxLogic::addPlayer(int id) {

    this->createCar(id);
}

void BoxLogic::update(Command &command) {
    // Si es comando de unirse llamo a addPlayer()
}

void BoxLogic::update() {
    // Es necesario?
}

BoxLogic::~BoxLogic() {
}

float BoxLogic::getData(int key, const b2Body* body) {
    switch (key) {
        case 0:
            return body->GetPosition().x;
        case 1:
            return body->GetPosition().y;
        case 2:
            return body->GetAngle();
        case 3:
            return body->GetLinearVelocity().x;
        case 4:
            return body->GetLinearVelocity().y;
    }

    // posiblemente no queres retornar un dummy.
    // Si sabes q key debe ser [0, 4], entonces
    // es mejor lanzar una excepcion y q rompa.
    return 0;
}



float BoxLogic::getBallData(int key) {
    return (this->getData(key, ball));
}

int BoxLogic::playersAmount() {
    return this->cars.size();
}

float BoxLogic::getCarData(int carNumber, int key) {
    return getCar(carNumber)->getData(key);
}

Car* BoxLogic::getCar(int carID) {
    for (auto &x : cars) {
        if (x.getId() == carID) {
            return &x;
        }
    }
    return nullptr;
}

b2Vec2 BoxLogic::getVectorForce(int direction) {
    if (direction == LogicValues().LEFT_DIRECTION)
        return b2Vec2(-2.0f, 0.0f);
    else if (direction == LogicValues().RIGHT_DIRECTION)
        return(b2Vec2(2.0f, 0.0f));
    else if (direction == LogicValues().UP_DIRECTION)
        return (b2Vec2(0.0f, -3.0f));
    return (b2Vec2(0.0f, -3.0f));
}

// Verificar si existe otra manera para no llamar siempre a force ()
void BoxLogic::startMove(int carNumber, bool direction) {
    b2Vec2 vel = getVectorForce((int)direction);
    getCar(carNumber)->startMove(vel);
}

void BoxLogic::stopMove(int carNumber) {
    getCar(carNumber)->stopMove();
}

void BoxLogic::jump(int carNumber) {
    b2Vec2 vel = getVectorForce((LogicValues().UP_DIRECTION));
    getCar(carNumber)->jump(vel);
}

PlayerResponses BoxLogic::getPlayersData() {
    std::vector<PlayerResponse> vector;
    for (auto &x : cars) {
        vector.emplace_back(x.getId(), x.getData(LogicValues().POS_X),
                            x.getData(LogicValues().POS_Y),
                            x.getData(LogicValues().ANGLE),
                            ((x.getData(LogicValues().X_VELOCITY) != 0) || (x.getData(LogicValues().Y_VELOCITY) != 0)),
                            (x.getData(LogicValues().POS_Y) < (2.23)),
                            x.getData(LogicValues().USING_TURBO),
                            false,
                            x.getData(LogicValues().ACCELERATING),
                            false);
    }
    return PlayerResponses(vector);
}


void BoxLogic::updateStatus() {
    verifyDoubleJump();
    verifyTurbo();
    verifyGoal();
    verifyAcceleration();
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

void BoxLogic::applyTurbo(int carNumber) {
    getCar(carNumber)->applyTurbo();
}

/*
 * teamGoal = 0 -> No hay goles
 * teamGoal = 1 -> Gol Local
 * teamGoal = 2 -> Gol visitante
 */
void BoxLogic::updateGoal() { // refactor -> crear objeto pelota.
    int teamGoal = 0;

    if((getData(LogicValues().POS_X,ball) > 3.3) && ((getData(LogicValues().POS_Y,ball)) > 0)) {
        teamGoal = 2;
    } else if ((getData(LogicValues().POS_X,ball) < (-3.3)) && ((getData(LogicValues().POS_Y,ball)) > 0)) {
        teamGoal = 1;
    }
    game.updateGame(teamGoal);
}

void BoxLogic::resetPositions() {
    if(game.goal()) {
        for (auto &x : cars) {
            x.resetPosition();
        }
        ball->SetLinearVelocity(b2Vec2(0,0));
        ball->SetTransform(b2Vec2(0, -2.8f),0);

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
