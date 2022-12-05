//
// Created by taller on 18/11/22.
//

#include "SoccerGoal.h"

SoccerGoal::SoccerGoal(b2Body *wall, b2Body *roof): wall(wall), roof(roof) {
}

void SoccerGoal::createFixtureRoof(b2FixtureDef & fixture) {
        roof->CreateFixture(&fixture);
    }

void SoccerGoal::createFixtureWall(b2FixtureDef & fixture) {
    wall->CreateFixture(&fixture);
}
