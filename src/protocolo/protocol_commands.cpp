#include <iostream>
#include <algorithm>
#include "protocol_commands.h"

ProtocolCommands::ProtocolCommands() : values(),
        deserializedCommands({
            {this->values.SERIALIZED_NOP, this->values.DESERIALIZED_NOP},
            {this->values.SERIALIZED_UP_PUSHED, this->values.DESERIALIZED_UP_PUSHED},
            {this->values.SERIALIZED_UP_RELEASE, this->values.DESERIALIZED_UP_RELEASE},
            {this->values.SERIALIZED_DOWN_PUSHED, this->values.DESERIALIZED_DOWN_PUSHED},
            {this->values.SERIALIZED_DOWN_RELEASE, this->values.DESERIALIZED_DOWN_RELEASE},
            {this->values.SERIALIZED_LEFT_PUSHED, this->values.DESERIALIZED_LEFT_PUSHED},
            {this->values.SERIALIZED_LEFT_RELEASE, this->values.DESERIALIZED_LEFT_RELEASE},
            {this->values.SERIALIZED_RIGHT_PUSHED, this->values.DESERIALIZED_RIGHT_PUSHED},
            {this->values.SERIALIZED_RIGHT_RELEASE, this->values.DESERIALIZED_RIGHT_RELEASE},
            {this->values.SERIALIZED_TURBO_RELEASE, this->values.DESERIALIZED_TURBO_RELEASE},
            {this->values.SERIALIZED_TURBO_PUSHED, this->values.DESERIALIZED_TURBO_PUSHED},
            {this->values.SERIALIZED_JUMP_RELEASE, this->values.DESERIALIZED_JUMP_RELEASE},
            {this->values.SERIALIZED_JUMP_PUSHED, this->values.DESERIALIZED_JUMP_PUSHED},
            {this->values.SERIALIZED_LIST, this->values.DESERIALIZED_LIST},
            {this->values.SERIALIZED_CREATE, this->values.DESERIALIZED_CREATE},
            {this->values.SERIALIZED_JOIN, this->values.DESERIALIZED_JOIN},
            {this->values.SERIALIZED_QUIT_MATCH, this->values.DESERIALIZED_QUIT_MATCH},
            {this->values.SERIALIZED_QUIT_GAME, this->values.DESERIALIZED_QUIT_GAME},
        }),
        serializedCommands({
            {this->values.DESERIALIZED_NOP, this->values.SERIALIZED_NOP},
            {this->values.DESERIALIZED_UP_PUSHED, this->values.SERIALIZED_UP_PUSHED},
            {this->values.DESERIALIZED_UP_RELEASE, this->values.SERIALIZED_UP_RELEASE},
            {this->values.DESERIALIZED_DOWN_PUSHED, this->values.SERIALIZED_DOWN_PUSHED},
            {this->values.DESERIALIZED_DOWN_RELEASE, this->values.SERIALIZED_DOWN_RELEASE},
            {this->values.DESERIALIZED_LEFT_PUSHED, this->values.SERIALIZED_LEFT_PUSHED},
            {this->values.DESERIALIZED_LEFT_RELEASE, this->values.SERIALIZED_LEFT_RELEASE},
            {this->values.DESERIALIZED_RIGHT_PUSHED, this->values.SERIALIZED_RIGHT_PUSHED},
            {this->values.DESERIALIZED_RIGHT_RELEASE, this->values.SERIALIZED_RIGHT_RELEASE},
            {this->values.DESERIALIZED_TURBO_RELEASE, this->values.SERIALIZED_TURBO_RELEASE},
            {this->values.DESERIALIZED_TURBO_PUSHED, this->values.SERIALIZED_TURBO_PUSHED},
            {this->values.DESERIALIZED_JUMP_RELEASE, this->values.SERIALIZED_JUMP_RELEASE},
            {this->values.DESERIALIZED_JUMP_PUSHED, this->values.SERIALIZED_JUMP_PUSHED},
            {this->values.DESERIALIZED_LIST, this->values.SERIALIZED_LIST},
            {this->values.DESERIALIZED_CREATE, this->values.SERIALIZED_CREATE},
            {this->values.DESERIALIZED_JOIN, this->values.SERIALIZED_JOIN},
            {this->values.DESERIALIZED_QUIT_MATCH, this->values.SERIALIZED_QUIT_MATCH},
            {this->values.DESERIALIZED_QUIT_GAME, this->values.SERIALIZED_QUIT_GAME},
            }){}

Command ProtocolCommands::createCommand(int id,
                                        std::string &value) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return {id, position->second, position->first};
}

Command ProtocolCommands::createCommand(int id,
                                        std::string &value,
                                        std::string &firstParameter) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return {id, position->second, position->first, firstParameter};
}

Command ProtocolCommands::createCommand(int id,
                                        std::string &value,
                                        std::string &firstParameter,
                                        std::string &secondParameter) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return {id, position->second, position->first, firstParameter, secondParameter};
}

std::string ProtocolCommands::getDeserializedCommandValue(unsigned char serialized) {
    auto position = this->deserializedCommands.find(serialized);

    if (position == this->deserializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return position->second;
}
