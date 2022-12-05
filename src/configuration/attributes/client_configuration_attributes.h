#ifndef CLIENT_CONFIGURATION_ATTRIBUTES_H
#define CLIENT_CONFIGURATION_ATTRIBUTES_H


class ClientConfigurationAttributes {
private:
    int windowWidth;
public:
    int getWindowWidth() const;

    int getWindowHeight() const;

    float getCarWidth() const;

    float getCarHeight() const;

    float getBallRadius() const;

    int getGameTime() const;

private:
    int windowHeight;

    float carWidth;
    float carHeight;
    float ballRadius;

    int gameTime;
public:
    ClientConfigurationAttributes(int windowWidth, int windowHeight,
                                  float carWidth, float carHeight,
                                  float ballRadius, int gameTime);
};


#endif // CLIENT_CONFIGURATION_ATTRIBUTES_H
