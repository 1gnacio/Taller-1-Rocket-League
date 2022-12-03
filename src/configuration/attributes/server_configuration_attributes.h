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

    float ballRadious;
    float mapGravity;

    float movementForceModule;
    float jumpImpulse;

    int replayTimeInSec;
    int responsesPerSec;

public:
    ServerConfigurationAttributes(float carWidth, float carHeight, float carDensity,
                                  float carFriction, float carRestitution, float ballDensity, float ballFriction,
                                  float ballRestitution, float ballRadious, float mapGravity, float movementForceModule,
                                  float jumpImpulse, int replayTimeInSec, int responsesPerSec);
};


#endif // SERVER_CONFIGURATION_ATTRIBUTES_H
