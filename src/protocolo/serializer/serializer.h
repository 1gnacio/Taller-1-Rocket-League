#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <vector>
#include <string>

class Serializer {
public:

    [[nodiscard]] float deserializeFloat(const std::vector<unsigned char> &serializedInt) const;
    [[nodiscard]] int deserializeInt(const std::vector<unsigned char> &serializedInt) const;
    [[nodiscard]] bool deserializeBool(const std::vector<unsigned char> &serializedBool) const;
    [[nodiscard]] std::string deserializeString(const std::vector<unsigned char> &serializedString) const;

    void parse(int &integer, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(float &decimal, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(bool &boolean, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);
    void parse(std::string &string, std::vector<unsigned char> &serialization, int &beginPosition, int &endPosition);

    std::vector<unsigned char> serializeInt(int value);
    std::vector<unsigned char> serializeFloat(float value);
    std::vector<unsigned char> serializeBool(bool value);
    std::vector<unsigned char> serializeString(std::string& value);

    void merge(std::vector<unsigned char> &firstVector, std::vector<unsigned char> lastVector);
};


#endif // SERIALIZER_H
