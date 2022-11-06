//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H

#include <string>
#include <vector>

class PlayerResponse {
private:
    float posX;
    float posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool isTurboActivated;
    bool hasPunchedTheBall;
    bool isAccelerating;
    bool isLocalTeam;
    int id;

public:
    std::vector<char> serialize();
};


#endif //TALLER_1_ROCKET_LEAGUE_PLAYERRESPONSE_H
