#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <vector>

class Serializer {
private:

    float deserializeFloat(const std::vector<unsigned char> &serializedInt) const;
    int deserializeInt(const std::vector<unsigned char> &serializedInt) const;
    bool deserializeBool(const std::vector<unsigned char> &serializedBool) const;

public:

    void merge(std::vector<unsigned char> &firstVector, std::vector<unsigned char> lastVector);

    void parse(int &integer, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(float &decimal, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(bool &boolean, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);

    std::vector<unsigned char> serializeInt(int value);
    std::vector<unsigned char> serializeFloat(float value);
    std::vector<unsigned char> serializeBool(bool value);
};


#endif // SERIALIZER_H
