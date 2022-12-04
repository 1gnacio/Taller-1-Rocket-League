#include "server_configuration_attributes.h"

ServerConfigurationAttributes::ServerConfigurationAttributes(float carWidth, float carHeight,
                                                             float carDensity, float carFriction, float carRestitution,
                                                             float ballDensity, float ballFriction,
                                                             float ballRestitution, float ballRadius, float mapGravity,
                                                             float movementForceModule, float jumpImpulse,
                                                             int replayTimeInSec, int responsesPerSec) :
                                                             carWidth(carWidth), carHeight(carHeight),
                                                             carDensity(carDensity), carFriction(carFriction),
                                                             carRestitution(carRestitution), ballDensity(ballDensity),
                                                             ballFriction(ballFriction),
                                                             ballRestitution(ballRestitution), ballRadius(ballRadius),
                                                             mapGravity(mapGravity),
                                                             movementForceModule(movementForceModule),
                                                             jumpImpulse(jumpImpulse), replayTimeInSec(replayTimeInSec),
                                                             responsesPerSec(responsesPerSec) {}

float ServerConfigurationAttributes::getCarWidth() const {
    return carWidth;
}

float ServerConfigurationAttributes::getCarHeight() const {
    return carHeight;
}

float ServerConfigurationAttributes::getCarDensity() const {
    return carDensity;
}

float ServerConfigurationAttributes::getCarFriction() const {
    return carFriction;
}

float ServerConfigurationAttributes::getCarRestitution() const {
    return carRestitution;
}

float ServerConfigurationAttributes::getBallDensity() const {
    return ballDensity;
}

float ServerConfigurationAttributes::getBallFriction() const {
    return ballFriction;
}

float ServerConfigurationAttributes::getBallRestitution() const {
    return ballRestitution;
}

float ServerConfigurationAttributes::getBallRadius() const {
    return ballRadius;
}

float ServerConfigurationAttributes::getMapGravity() const {
    return mapGravity;
}

float ServerConfigurationAttributes::getMovementForceModule() const {
    return movementForceModule;
}

float ServerConfigurationAttributes::getJumpImpulse() const {
    return jumpImpulse;
}

int ServerConfigurationAttributes::getReplayTimeInSec() const {
    return replayTimeInSec;
}

int ServerConfigurationAttributes::getResponsesPerSec() const {
    return responsesPerSec;
}
