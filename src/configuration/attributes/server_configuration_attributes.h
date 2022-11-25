#ifndef SERVER_CONFIGURATION_ATTRIBUTES_H
#define SERVER_CONFIGURATION_ATTRIBUTES_H


class ServerConfigurationAttributes {
private:
    float maxTurboQuantity;
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

public:
    ServerConfigurationAttributes(float maxTurboQuantity, float carWidth, float carHeight, float carDensity,
                                  float carFriction, float carRestitution, float ballDensity, float ballFriction,
                                  float ballRestitution, float ballRadious, float mapGravity, float movementForceModule,
                                  float jumpImpulse);
};


#endif // SERVER_CONFIGURATION_ATTRIBUTES_H
