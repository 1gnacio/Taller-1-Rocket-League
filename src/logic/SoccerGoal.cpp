//
// Created by taller on 18/11/22.
//

#include "SoccerGoal.h"

SoccerGoal::SoccerGoal(b2Body *wall, b2Body *roof, b2Body* floor): wall(wall), roof(roof), floor(floor) {
}

void SoccerGoal::createFixtureRoof(b2FixtureDef & fixture) {
        roof->CreateFixture(&fixture);
    }

void SoccerGoal::createFixtureWall(b2FixtureDef & fixture) {
    wall->CreateFixture(&fixture);
}

b2Vec2 SoccerGoal::getPositionWall() {
    return wall->GetPosition();
}

b2Vec2 SoccerGoal::getPositionRoof() {
    return roof->GetPosition();
}

void SoccerGoal::createFixtureFloor(b2FixtureDef &def) {
    floor->CreateFixture(&def);

}
