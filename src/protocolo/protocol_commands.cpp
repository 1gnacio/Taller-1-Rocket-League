#include <iostream>
#include <algorithm>
#include "protocol_commands.h"
#include "../protocolo/commands/strategies/create_parameter_strategy.h"

ProtocolCommands::ProtocolCommands() : values(),
        serializedCommands({
            {this->values.DESERIALIZED_UP_PUSHED, this->values.SERIALIZED_UP_PUSHED},
            {this->values.DESERIALIZED_UP_RELEASE, this->values.SERIALIZED_UP_RELEASE},
            {this->values.DESERIALIZED_DOWN_PUSHED, this->values.SERIALIZED_DOWN_PUSHED},
            {this->values.DESERIALIZED_DOWN_RELEASE, this->values.SERIALIZED_DOWN_RELEASE},
            {this->values.DESERIALIZED_LEFT_PUSHED, this->values.SERIALIZED_LEFT_PUSHED},
            {this->values.DESERIALIZED_LEFT_RELEASE, this->values.SERIALIZED_LEFT_RELEASE},
            {this->values.DESERIALIZED_RIGHT_PUSHED, this->values.SERIALIZED_RIGHT_PUSHED},
            {this->values.DESERIALIZED_RIGHT_RELEASE, this->values.SERIALIZED_RIGHT_RELEASE}
        }),
        deserializedCommands({
            {this->values.SERIALIZED_UP_PUSHED, this->values.DESERIALIZED_UP_PUSHED},
            {this->values.SERIALIZED_UP_RELEASE, this->values.DESERIALIZED_UP_RELEASE},
            {this->values.SERIALIZED_DOWN_PUSHED, this->values.DESERIALIZED_DOWN_PUSHED},
            {this->values.SERIALIZED_DOWN_RELEASE, this->values.DESERIALIZED_DOWN_RELEASE},
            {this->values.SERIALIZED_LEFT_PUSHED, this->values.DESERIALIZED_LEFT_PUSHED},
            {this->values.SERIALIZED_LEFT_RELEASE, this->values.DESERIALIZED_LEFT_RELEASE},
            {this->values.SERIALIZED_RIGHT_PUSHED, this->values.DESERIALIZED_RIGHT_PUSHED},
            {this->values.SERIALIZED_RIGHT_RELEASE, this->values.DESERIALIZED_RIGHT_RELEASE}
        }),
        parameteredCommands({this->values.DESERIALIZED_JOIN, this->values.DESERIALIZED_CREATE}){
}

Command ProtocolCommands::createParameteredCommand(const char serialized,
                                                   const std::string &deserialized,
                                                   std::string &arguments) {
    if (deserialized == this->values.DESERIALIZED_CREATE) {
        CreateParameterStrategy parameters;
        return Command(serialized,
                       deserialized,
                       parameters.firstParameter(arguments),
                       parameters.secondParameter(arguments));
    }

    return Command(serialized, deserialized, arguments);
}

Command ProtocolCommands::createCommand(std::string &value) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return Command(position->second, position->first);
}

Command ProtocolCommands::createSimpleCommand(const char serialized, const std::string &deserialized) const {
    return Command(serialized, deserialized);
}

Command ProtocolCommands::createCommand(std::vector<char> &serializedCommand) {
    auto position = this->deserializedCommands.find(serializedCommand[0]);

    if (position == this->deserializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    auto parametered = std::find(this->parameteredCommands.begin(),
                                                            this->parameteredCommands.end(),
                                                            position->second);

    if (parametered == this->parameteredCommands.end()) {
        return this->createSimpleCommand(position->first,
                                         position->second);
    }

    std::string arguments(serializedCommand.begin() + 1,
                          serializedCommand.end());

    return this->createParameteredCommand(position->first,
                                          position->second,
                                          arguments);
}