#ifndef COMMAND_VALUES_H
#define COMMAND_VALUES_H

#include <string>

class CommandValues {
public:
    const unsigned char SERIALIZED_NOP = 0x00;

    const unsigned char SERIALIZED_RIGHT_PUSHED = 0x10;
    const unsigned char SERIALIZED_RIGHT_RELEASE = 0x11;
    const unsigned char SERIALIZED_LEFT_PUSHED = 0x12;
    const unsigned char SERIALIZED_LEFT_RELEASE = 0x13;
    const unsigned char SERIALIZED_UP_PUSHED = 0x14;
    const unsigned char SERIALIZED_UP_RELEASE = 0x15;
    const unsigned char SERIALIZED_DOWN_PUSHED = 0x16;
    const unsigned char SERIALIZED_DOWN_RELEASE = 0x17;

    const unsigned char SERIALIZED_JUMP_PUSHED = 0x20;
    const unsigned char SERIALIZED_JUMP_RELEASE = 0x21;
    const unsigned char SERIALIZED_TURBO_PUSHED = 0x22;
    const unsigned char SERIALIZED_TURBO_RELEASE = 0x23;

    const unsigned char SERIALIZED_LIST = 0x30;
    const unsigned char SERIALIZED_CREATE = 0x31;
    const unsigned char SERIALIZED_JOIN = 0x32;
    const unsigned char SERIALIZED_QUIT_MATCH = 0x33;
    const unsigned char SERIALIZED_QUIT_GAME = 0x34;

    const std::string DESERIALIZED_NOP = "NOP";

    const std::string DESERIALIZED_RIGHT_PUSHED = "RIGHT_PUSHED";
    const std::string DESERIALIZED_RIGHT_RELEASE = "RIGHT_RELEASE";
    const std::string DESERIALIZED_LEFT_PUSHED = "LEFT_PUSHED";
    const std::string DESERIALIZED_LEFT_RELEASE = "LEFT_RELEASE";
    const std::string DESERIALIZED_UP_PUSHED = "UP_PUSHED";
    const std::string DESERIALIZED_UP_RELEASE = "UP_RELEASE";
    const std::string DESERIALIZED_DOWN_PUSHED = "DOWN_PUSHED";
    const std::string DESERIALIZED_DOWN_RELEASE = "DOWN_RELEASE";

    const std::string DESERIALIZED_JUMP_PUSHED = "JUMP_PUSHED";
    const std::string DESERIALIZED_JUMP_RELEASE = "JUMP_RELEASE";
    const std::string DESERIALIZED_TURBO_PUSHED = "TURBO_PUSHED";
    const std::string DESERIALIZED_TURBO_RELEASE = "TURBO_RELEASE";

    const std::string DESERIALIZED_LIST = "LIST";
    const std::string DESERIALIZED_CREATE = "CREATE";
    const std::string DESERIALIZED_JOIN = "JOIN";
    const std::string DESERIALIZED_QUIT_MATCH = "QUIT_MATCH";
    const std::string DESERIALIZED_QUIT_GAME = "QUIT_GAME";
};

#endif // COMMAND_VALUES_H
