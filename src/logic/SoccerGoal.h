#ifndef ROCKET_LEAGUE_SOCCERGOAL_H
#define ROCKET_LEAGUE_SOCCERGOAL_H

#include "../../box2d/include/box2d/box2d.h"

class SoccerGoal {
 private:
   b2Body* wall;
   b2Body* roof;
   b2Body* floor;

 public:
   SoccerGoal(b2Body* wall, b2Body* roof, b2Body* floor);
    void createFixtureRoof(b2FixtureDef & fixture);

    void createFixtureWall(b2FixtureDef & fixture);
    b2Vec2 getPositionWall();
    b2Vec2 getPositionRoof();

    void createFixtureFloor(b2FixtureDef &def);
};
#endif //ROCKET_LEAGUE_SOCCERGOAL_H
