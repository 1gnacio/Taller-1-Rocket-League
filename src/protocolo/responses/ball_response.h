//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_BALL_RESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_BALL_RESPONSE_H

#include <string>
#include <vector>

class BallResponse {
private:
    std::string posX;
    std::string posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool hasBeenPunched;
public:
    std::vector<char> serialize();
};


#endif //TALLER_1_ROCKET_LEAGUE_BALL_RESPONSE_H
