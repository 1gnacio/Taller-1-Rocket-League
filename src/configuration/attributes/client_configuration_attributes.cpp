#include "client_configuration_attributes.h"

ClientConfigurationAttributes::ClientConfigurationAttributes(int windowWidth, int windowHeight,
                                                             float carWidth, float carHeight,
                                                             float ballRadius, int gameTime) :
                                                             windowWidth(windowWidth), windowHeight(windowHeight),
                                                             carWidth(carWidth), carHeight(carHeight),
                                                             ballRadius(ballRadius), gameTime(gameTime){}

int ClientConfigurationAttributes::getWindowWidth() const {
    return windowWidth;
}

int ClientConfigurationAttributes::getWindowHeight() const {
    return windowHeight;
}

float ClientConfigurationAttributes::getCarWidth() const {
    return carWidth;
}

float ClientConfigurationAttributes::getCarHeight() const {
    return carHeight;
}

float ClientConfigurationAttributes::getBallRadius() const {
    return ballRadius;
}

int ClientConfigurationAttributes::getGameTime() const {
    return gameTime;
}
