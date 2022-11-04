//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H

#include <string>
#include <vector>

class PlayerResponse {
private:
    std::string posX;
    std::string posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool isTurboActivated;
    bool hasPunchedTheBall;
    bool isAccelerating;

public:
    std::vector<char> serialize();
};


#endif //TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H