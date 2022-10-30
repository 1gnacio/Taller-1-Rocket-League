//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
#define TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H

#include <map>
#include <string>
#include <vector>
#include "command.h"

class ProtocolCommands {
private:
    std::map<char, std::string> deserializedCommands;
    std::map<std::string, char> serializedCommands;
public:
    ProtocolCommands();

    Command createMovementCommand(std::string& value);
    std::vector<Command> createCommandSequence(std::vector<std::string>& receivedInput);

    char SERIALIZED_NOP = 0x00;

    char SERIALIZED_JUMP_PUSHED = 0x20;
    char SERIALIZED_JUMP_RELEASE = 0x21;
    char SERIALIZED_TURBO_PUSHED = 0x22;
    char SERIALIZED_TURBO_RELEASE = 0x23;
    char SERIALIZED_RIGHT_PUSHED = 0x10;
    char SERIALIZED_RIGHT_RELEASE = 0x11;
    char SERIALIZED_LEFT_PUSHED = 0x12;
    char SERIALIZED_LEFT_RELEASE = 0x13;
    char SERIALIZED_UP_PUSHED = 0x14;
    char SERIALIZED_UP_RELEASE = 0x15;
    char SERIALIZED_DOWN_PUSHED = 0x16;
    char SERIALIZED_DOWN_RELEASE = 0x17;
    char SERIALIZED_LIST = 0x30;
    char SERIALIZED_CREATE = 0x31;
    char SERIALIZED_JOIN = 0x32;

    std::string DESERIALIZED_NOP = "NOP";

    std::string DESERIALIZED_JUMP_PUSHED = "JUMP_PUSHED";
    std::string DESERIALIZED_JUMP_RELEASE = "JUMP_RELEASE";
    std::string DESERIALIZED_RIGHT_PUSHED = "RIGHT_PUSHED";
    std::string DESERIALIZED_RIGHT_RELEASE = "RIGHT_RELEASE";
    std::string DESERIALIZED_LEFT_PUSHED = "LEFT_PUSHED";
    std::string DESERIALIZED_LEFT_RELEASE = "LEFT_RELEASE";
    std::string DESERIALIZED_UP_PUSHED = "UP_PUSHED";
    std::string DESERIALIZED_UP_RELEASE = "UP_RELEASE";
    std::string DESERIALIZED_DOWN_PUSHED = "DOWN_PUSHED";
    std::string DESERIALIZED_DOWN_RELEASE = "DOWN_RELEASE";
    std::string DESERIALIZED_TURBO_PUSHED = "TURBO_PUSHED";
    std::string DESERIALIZED_TURBO_RELEASE = "TURBO_RELEASE";
    std::string DESERIALIZED_LIST = "LIST";
    std::string DESERIALIZED_CREATE = "CREATE";
    std::string DESERIALIZED_JOIN = "JOIN";
};


#endif //TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
