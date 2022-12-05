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
    bool hasBeenPunchedNormal;
    bool hasBeenPunchedFlipShot;
    bool hasBeenPunchedRedShot;
    bool hasBeenPunchedPurpleShot;
    bool hasBeenPunchedGoldShot;

public:
    BallResponse(float posX, float posY, float rotationAngle, bool isMoving, bool isFlying,
                 bool hasBeenPunchedNormal, bool hasBeenPunchedFlipShot, bool hasBeenPunchedRedShot,
                 bool hasBeenPunchedPurpleShot, bool hasBeenPunchedGoldShot);
    BallResponse(std::vector<unsigned char > serialized);
    BallResponse();
    std::vector<unsigned char> serialize();

    [[nodiscard]] float getPosX() const { return this->posX; }
    [[nodiscard]] float getPosY() const { return this->posY; }
    [[nodiscard]] float getRotationAngle() const { return this->rotationAngle; }
    [[nodiscard]] bool getIsMoving() const { return this->isMoving; }
    [[nodiscard]] bool getIsFlying() const { return this->isFlying; }
    [[nodiscard]] bool getHasBeenPunched() const { return (this->hasBeenPunchedNormal
            or this->hasBeenPunchedFlipShot or this->hasBeenPunchedGoldShot
            or this->hasBeenPunchedPurpleShot or this->hasBeenPunchedRedShot); }
    [[nodiscard]] bool getHasBeenPunchedNormal() const { return this->hasBeenPunchedNormal; }
    [[nodiscard]] bool getHasBeenPunchedFlipShot() const { return this->hasBeenPunchedFlipShot; }
    [[nodiscard]] bool getHasBeenPunchedRedShot() const { return this->hasBeenPunchedRedShot; }
    [[nodiscard]] bool getHasBeenPunchedGoldShot() const { return this->hasBeenPunchedGoldShot; }
    [[nodiscard]] bool getHasBeenPunchedPurpleShot() const { return this->hasBeenPunchedPurpleShot; }
    static int size();
};


#endif // BALL_RESPONSE_H
