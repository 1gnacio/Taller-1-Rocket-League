#include "client_configuration_attributes.h"

ClientConfigurationAttributes::ClientConfigurationAttributes(int windowWidth, int windowHeight,
                                                             float carWidth, float carHeight,
                                                             float ballRadius, int gameTime, bool sound, unsigned int updateTime) :
                                                             windowWidth(windowWidth), windowHeight(windowHeight),
                                                             carWidth(carWidth), carHeight(carHeight),
                                                             ballRadius(ballRadius), gameTime(gameTime), sound(sound),
                                                             updateTime(updateTime){}

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

bool ClientConfigurationAttributes::enableSound() const {
    return sound;
}

unsigned int ClientConfigurationAttributes::getUpdateTime() const {
    return updateTime;
}

