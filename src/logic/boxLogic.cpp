//
// Created by taller on 06/11/22.
//
//Box2d en una escala de 4 | 3
#include "boxLogic.h"
#include <iostream>
#include <unistd.h>

BoxLogic::BoxLogic():
    isActive(true),
    steps(std::thread(&BoxLogic::updateTime, this)){
    world = std::make_unique<b2World>(b2Vec2(0.0f,9.8f));
    createWalls();
    createBall();

}

b2Vec2 BoxLogic::getGravity(){
    return this->world->GetGravity();
}

int BoxLogic::wallsAmount(){
    return this->walls.size();
}
void BoxLogic::close(){
    isActive = false;
}

void BoxLogic::updateTime(){
    float timeStep = 1.0f / 5.0f;
    while(this->isActive){ // Se hara false con algun comando definido
        {
            std::lock_guard<std::mutex> lock(mutex);
            world->Step(timeStep,8,3);
        }
       sleep(1); // Simulacion paso tiempo
    }
}

bool BoxLogic::ballIsAwake() {
    ball->IsAwake();
}
void BoxLogic::createBall(){
    std::lock_guard<std::mutex> lock(mutex);

    b2BodyDef ballDef;
    ballDef.type = b2_dynamicBody;
    ballDef.position.Set(0,-2.8f);
    this->ball = world->CreateBody(&ballDef);

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
    std::lock_guard<std::mutex> lock(mutex);
    //tamaño de auto
    float wCar = 1.2;
    float hCar = 0.5;

    b2BodyDef carBodyDef;
    carBodyDef.type = b2_dynamicBody;
    carBodyDef.angle = 0;
    carBodyDef.position.Set(2.0f,-2.0f);
    cars.push_back(world->CreateBody(&carBodyDef));
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
    std::lock_guard<std::mutex> lock(mutex);
    float ground_x = 0.0f;
    float ground_y = 0.0f;

    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set(ground_x,ground_y);
    groundDef.angle = 0;
    for(int i = 0; i < 4; i++){
        walls.emplace_back(this->world->CreateBody(&groundDef));
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
}

float BoxLogic::getBallData(int key) {
    return (this->getData(key, ball));
}

int BoxLogic::playersAmount() {
    return this->cars.size();
}

float BoxLogic::getCarData(int carNumber, int key) {
    return this->getData(key, getCar(carNumber));
}

b2Body* BoxLogic::getCar(int carNumber) {
    int i = 1;
    for(auto x : cars ){
        if(i == carNumber){
            return x;
        }
    }
}

b2Vec2 BoxLogic::getVectorForce(int direction) {
    if(direction == 0)
        return b2Vec2(-2.0f, 0.0f);
    else if(direction == 1)
        return(b2Vec2(2.0f,0.0f));
    else if(direction == 2)
        return (b2Vec2(0.0f,-3.0f));
}

// Verificar si existe otra manera para no llamar siempre a force ()
void BoxLogic::startMove(int carNumber, bool direction) {
    b2Vec2 vel = getVectorForce((int)direction);
    getCar(carNumber)->SetLinearVelocity(vel);
}

void BoxLogic::stopMove(int carNumber) {
    getCar(carNumber)->SetLinearVelocity(b2Vec2(0.0f,0.0f));

}

void BoxLogic::jump(int carNumber) {
    b2Vec2 vel = getVectorForce((2));
    if(getCar(carNumber)->GetPosition().y >= 2 ) {
        getCar(carNumber)->ApplyLinearImpulseToCenter(vel,true);
    }
}
