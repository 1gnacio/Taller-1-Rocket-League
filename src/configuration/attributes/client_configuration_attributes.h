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

    bool enableSound() const;

    unsigned int getUpdateTime() const;

private:
    int windowHeight;
    bool sound;
    float carWidth;
    float carHeight;
    float ballRadius;
    unsigned int updateTime;
    int gameTime;
public:
    ClientConfigurationAttributes(int windowWidth, int windowHeight,
                                  float carWidth, float carHeight,
                                  float ballRadius, int gameTime, bool sound,
                                  unsigned int updateTime);
};


#endif // CLIENT_CONFIGURATION_ATTRIBUTES_H
