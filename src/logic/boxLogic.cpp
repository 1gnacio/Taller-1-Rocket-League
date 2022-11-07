//
// Created by taller on 06/11/22.
//
//Box2d en una escala de 4 | 3
#include "boxLogic.h"

BoxLogic::BoxLogic():
    world(b2Vec2(0.0f,9.8f)),
    isActive(true),
    steps(std::thread(&BoxLogic::updateTime, this)){
    //createWalls();
    //createBall();
}

void BoxLogic::updateTime(){
    while(this->isActive){ // Se hara false con algun comando definido
        world.Step(1/60,6,2);
    }
}
void BoxLogic::createBall(){

    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(0,-2.8f);
    this->ball = world.CreateBody(&ballDef);

    b2CircleShape shapeCircle;
    shapeCircle.m_radius = 0.2;

    b2FixtureDef fixtureCircle;
    fixtureCircle.shape = &shapeCircle;
    fixtureCircle.density = 0.5;
    fixtureCircle.friction = 0.3f;
    fixtureCircle.restitution = 0.6f;
    ball->CreateFixture(&fixtureCircle);

}

void BoxLogic::createCar() {
    //tamaño de auto
    float wCar = 1.2;
    float hCar = 0.5;

    b2BodyDef carBodyDef;
    carBodyDef.type = b2_dynamicBody;
    carBodyDef.angle = 0;
    carBodyDef.position.Set(2.0f,-2.0f);
    cars.emplace_back(this->world.CreateBody(&carBodyDef));

    b2PolygonShape dynamicCar;
    dynamicCar.SetAsBox(wCar/2.0f,hCar/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCar;
    fixtureDef.density = 1;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.0f;
    cars.back()->CreateFixture(&fixtureDef);
}

void BoxLogic::createWalls() {

    float ground_x = 0.0f;
    float ground_y = 0.0f;

    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(ground_x,ground_y);
    groundDef.angle = 0;
    for(int i = 0; i < 4; i++){
        walls.emplace_back(this->world.CreateBody(&groundDef));
    }
    b2FixtureDef edgeFixtureDef;
    b2EdgeShape edge;
    float edgesXStart[] = {-4.0f,-4.0f,4.0f,-4.0f};
    float edgesXEnd[] = {4.0f,-4.0f,4.0f, 4.0f};
    float edgesYStart[] = {2.5f,-3.0f,-3.0f, -3.0f};
    float edgesYEnd[] = {2.5f,3.0f,3.0f, -3.0f};

    int i = 0;
    for(auto x: walls){
        edge.SetTwoSided(b2Vec2(edgesXStart[i],edgesYStart[i]), b2Vec2(edgesXEnd[i],edgesYEnd[i]));
        edgeFixtureDef.shape = &edge;
        x->CreateFixture(&edgeFixtureDef);
        i++;
    }
}

void BoxLogic::addPlayer() {
    this->createCar();
}

void BoxLogic::update(Command &command) {
    // Si es comando de unirse llamo a addPlayer()
}

void BoxLogic::update() {
    // Es necesario?
}

BoxLogic::~BoxLogic(){
 this->steps.join();
}