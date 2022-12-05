#ifndef SERVER_CONFIGURATION_ATTRIBUTES_H
#define SERVER_CONFIGURATION_ATTRIBUTES_H


class ServerConfigurationAttributes {
private:
    float carWidth;
    float carHeight;

    float carDensity;
    float carFriction;
    float carRestitution;

    float ballDensity;
    float ballFriction;
    float ballRestitution;

    float ballRadius;
    float mapGravity;

    float movementForceModule;
    float jumpImpulse;

    int replayTimeInSec;
    int responsesPerSec;
    int gameTime;

    float forceFlipShot;
    float forceRedShot;
    float forcePurpleShot;
    float forceGoldShot;

    float turboForce;
    float torqueForce;
public:
    float getTorqueForce() const;

public:
    float getCarWidth() const;

    float getCarHeight() const;

    float getCarDensity() const;

    float getCarFriction() const;

    float getCarRestitution() const;

    float getBallDensity() const;

    float getBallFriction() const;

    float getBallRestitution() const;

    float getBallRadius() const;

    float getMapGravity() const;

    float getMovementForceModule() const;

    float getJumpImpulse() const;

    int getReplayTimeInSec() const;

    int getResponsesPerSec() const;

    float getForceFlipShot() const;

    float getForceRedShot() const;

    float getForcePurpleShot() const;

    float getForceGoldShot() const;

    float getTurboForce() const;

    int getGameTime() const;


public:
    ServerConfigurationAttributes(float carWidth, float carHeight, float carDensity,
                                  float carFriction, float carRestitution, float ballDensity, float ballFriction,
                                  float ballRestitution, float ballRadius, float mapGravity, float movementForceModule,
                                  float jumpImpulse, int replayTimeInSec, int responsesPerSec, int gameTime,
                                  float forceFlipShot, float forceRedShot, float forcePurpleShot, float forceGoldShot, float turboForce, float torqueForce);
};


#endif // SERVER_CONFIGURATION_ATTRIBUTES_H
