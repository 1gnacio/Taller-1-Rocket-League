#ifndef SRC_LOGIC_SOCCERGOAL_H_
#define SRC_LOGIC_SOCCERGOAL_H_

#include "../../box2d/include/box2d/box2d.h"

class SoccerGoal {
 private:
    b2Body* wall;
    b2Body* roof;

 public:
    SoccerGoal(b2Body* wall, b2Body* roof);
    void createFixtureRoof(b2FixtureDef &fixture);

    void createFixtureWall(b2FixtureDef &fixture);
    b2Vec2 getPositionWall();
    b2Vec2 getPositionRoof();
};
#endif  // SRC_LOGIC_SOCCERGOAL_H_
