#ifndef PLAYERRESPONSE_H
#define PLAYERRESPONSE_H

#include <string>
#include <vector>

class PlayerResponse {
private:
    int id;
    float posX;
    float posY;
    float rotationAngle;
    bool isMoving;
    bool isFlying;
    bool isTurboActivated;
    bool hasPunchedTheBall;
    bool isAccelerating;
    bool isLocalTeam;

    void merge(std::vector<unsigned char> &firstVector, std::vector<unsigned char> lastVector);
    void parse(int &integer, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(float &decimal, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(bool &boolean, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);

    std::vector<unsigned char> serializeInt(int value);
    std::vector<unsigned char> serializeFloat(float value);
    std::vector<unsigned char> serializeBool(bool value);
    float deserializeFloat(const std::vector<unsigned char> &serializedInt) const;
    int deserializeInt(const std::vector<unsigned char> &serializedInt) const;
    bool deserializeBool(const std::vector<unsigned char> &serializedBool) const;

public:
    PlayerResponse(int id, float posX, float posY, float rotationAngle,
                   bool isMoving, bool isFlying, bool isTurboActivated,
                   bool hasPunchedTheBall, bool isAccelerating, bool isLocalTeam);
    PlayerResponse(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();

    int getId() { return this->id; }
    float getPosX() { return this->posX; }
};


#endif // PLAYERRESPONSE_H
