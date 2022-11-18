#ifndef ROCKET_LEAGUE_SOCCERGOAL_H
#define ROCKET_LEAGUE_SOCCERGOAL_H

#include "../../box2d/include/box2d/box2d.h"

class SoccerGoal {
 private:
   b2Body* wall;
   b2Body* roof;

 public:
   SoccerGoal(b2Body* wall, b2Body* roof);
    void createFixtureRoof(b2FixtureDef & fixture);

    void createFixtureWall(b2FixtureDef & fixture);
    b2Vec2 getPositionWall();
    b2Vec2 getPositionRoof();

};
#endif //ROCKET_LEAGUE_SOCCERGOAL_H
