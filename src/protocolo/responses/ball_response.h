#ifndef BALL_RESPONSE_H
#define BALL_RESPONSE_H

#include <string>
#include <vector>
#include "../serializer/serializer.h"

class BallResponse {
private:
    Serializer serializer;
    float posX;
    float posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool hasBeenPunched;
public:
    BallResponse(float posX, float posY, float rotationAngle, bool isMoving, bool isFlying, bool hasBeenPunched);
    BallResponse(std::vector<unsigned char > serialized);
    std::vector<unsigned char> serialize();

    [[nodiscard]] float getPosX() const { return this->posX; }
    [[nodiscard]] float getPosY() const { return this->posY; }
    [[nodiscard]] float getRotationAngle() const { return this->rotationAngle; }
    [[nodiscard]] bool getIsMoving() const { return this->isMoving; }
    [[nodiscard]] bool getIsFlying() const { return this->isFlying; }
    [[nodiscard]] bool getHasBeenPunched() const { return this->hasBeenPunched; }
};


#endif // BALL_RESPONSE_H
