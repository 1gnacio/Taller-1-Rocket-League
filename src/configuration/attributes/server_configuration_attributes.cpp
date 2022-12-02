#include "server_configuration_attributes.h"

ServerConfigurationAttributes::ServerConfigurationAttributes(float maxTurboQuantity, float carWidth, float carHeight,
                                                             float carDensity, float carFriction, float carRestitution,
                                                             float ballDensity, float ballFriction,
                                                             float ballRestitution, float ballRadious, float mapGravity,
                                                             float movementForceModule, float jumpImpulse) :
                                                             maxTurboQuantity(maxTurboQuantity), carWidth(carWidth),
                                                             carHeight(carHeight), carDensity(carDensity),
                                                             carFriction(carFriction), carRestitution(carRestitution),
                                                             ballDensity(ballDensity), ballFriction(ballFriction),
                                                             ballRestitution(ballRestitution), ballRadious(ballRadious),
                                                             mapGravity(mapGravity),
                                                             movementForceModule(movementForceModule),
                                                             jumpImpulse(jumpImpulse) {}