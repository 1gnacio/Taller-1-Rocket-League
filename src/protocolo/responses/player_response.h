#ifndef PLAYERRESPONSE_H
#define PLAYERRESPONSE_H

#include <string>
#include <vector>
#include "../serializer/serializer.h"

class PlayerResponse {
private:
    Serializer serializer;

    int id;
    float posX;
    float posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool isTurboActivated;
    bool hasPunchedTheBall;
    bool isAccelerating;
    bool isLocalTeam;
    int goals;
    int assists;
    int saves;
    bool facingLeft;
    float remainingTurbo;
public:
    PlayerResponse(int id, float posX, float posY, float rotationAngle,
                   bool isMoving, bool isFlying, bool isTurboActivated,
                   bool hasPunchedTheBall, bool isAccelerating, bool isLocalTeam);

    explicit PlayerResponse(std::vector<unsigned char> &serialized);

    PlayerResponse();

    std::vector<unsigned char> serialize();

    [[nodiscard]] int getId() const { return this->id; }
    [[nodiscard]] float getPosX() const { return this->posX; }

    static int size();
    float getPosX();
    float getPosY();
    float getRotationAngle() const { return rotationAngle; }
    bool moving() const { return isMoving; }
    bool flying() const { return isFlying; }
    bool accelerating() const { return isAccelerating; }
    bool onTurbo() const { return isTurboActivated; }
    bool localTeam() const { return isLocalTeam; }
    bool isFacingLeft() const {return facingLeft; }

};


#endif // PLAYERRESPONSE_H
