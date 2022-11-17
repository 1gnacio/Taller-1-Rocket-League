#include <iostream>
#include <algorithm>
#include "protocol_commands.h"
#include "../protocolo/commands/strategies/create_parameter_strategy.h"

ProtocolCommands::ProtocolCommands() : values(),
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
            {this->values.DESERIALIZED_JUMP_PUSHED, this->values.SERIALIZED_JUMP_PUSHED}
        }),
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
            {this->values.SERIALIZED_JUMP_PUSHED, this->values.DESERIALIZED_JUMP_PUSHED}
        }),
        parameteredCommands({this->values.DESERIALIZED_JOIN, this->values.DESERIALIZED_CREATE}){
}

Command ProtocolCommands::createParameteredCommand(int id, const unsigned char serialized,
                                                   const std::string &deserialized,
                                                   std::string &arguments) {
    if (deserialized == this->values.DESERIALIZED_CREATE) {
        CreateParameterStrategy parameters;
        return Command(id,
                       serialized,
                       deserialized,
                       parameters.firstParameter(arguments),
                       parameters.secondParameter(arguments));
    }

    return Command(id, serialized, deserialized, arguments);
}

Command ProtocolCommands::createCommand(int id, std::string &value) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return Command(id, position->second, position->first);
}

Command ProtocolCommands::createSimpleCommand(int id, const unsigned char serialized, const std::string &deserialized) const {
    return Command(id, serialized, deserialized);
}

Command ProtocolCommands::createCommand(std::vector<unsigned char> &serializedCommand) {
    auto position = this->deserializedCommands.find(serializedCommand[0]);
    std::vector<unsigned char> serializedInt(serializedCommand.begin() + 1, serializedCommand.begin() + 5);
    int id = Serializer().deserializeInt(serializedInt);

    if (position == this->deserializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    auto parametered = std::find(this->parameteredCommands.begin(),
                                 this->parameteredCommands.end(),
                                 position->second);

    if (parametered == this->parameteredCommands.end()) {
        return this->createSimpleCommand(id, position->first,
                                         position->second);
    }

    std::string arguments(serializedCommand.begin() + 5,
                          serializedCommand.end());

    return this->createParameteredCommand(id,
                                          position->first,
                                          position->second,
                                          arguments);
}

std::string ProtocolCommands::getDeserializedCommandValue(unsigned char commandValue) {
    auto position = this->deserializedCommands.find(commandValue);

    if (position == this->deserializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return position->second;
}
