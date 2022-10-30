//
// Created by ignacio on 30/10/22.
//

#include <iostream>
#include <algorithm>
#include "protocol_commands.h"

ProtocolCommands::ProtocolCommands()
: serializedCommands(
        {
            {this->DESERIALIZED_UP_PUSHED, this->SERIALIZED_UP_PUSHED},
            {this->DESERIALIZED_UP_RELEASE, this->SERIALIZED_UP_RELEASE},
            {this->DESERIALIZED_DOWN_PUSHED, this->SERIALIZED_DOWN_PUSHED},
            {this->DESERIALIZED_DOWN_RELEASE, this->SERIALIZED_DOWN_RELEASE},
            {this->DESERIALIZED_LEFT_PUSHED, this->SERIALIZED_LEFT_PUSHED},
            {this->DESERIALIZED_LEFT_RELEASE, this->SERIALIZED_LEFT_RELEASE},
            {this->DESERIALIZED_RIGHT_PUSHED, this->SERIALIZED_RIGHT_PUSHED},
            {this->DESERIALIZED_RIGHT_RELEASE, this->SERIALIZED_RIGHT_RELEASE}
        }) {}

Command ProtocolCommands::createMovementCommand(std::string& value) {
    auto position = this->serializedCommands.find(value);

    if (position == this->serializedCommands.end()) {
        throw std::runtime_error("Command not found");
    }

    return Command(position->second, value);
}

// en principio las secuencias de comandos solo se reciben mientras el jugador esta en partida
// manipulando el auto
std::vector <Command> ProtocolCommands::createCommandSequence(std::vector <std::string>& receivedInput) {
    std::vector<Command> result;

    if (!receivedInput.empty()) {
        std::transform(receivedInput.begin(),
                       receivedInput.end(),
                       result.begin(),
                       [this] (std::string& command) {
                           return this->createMovementCommand(command);
                       });
    }

    result.emplace_back(this->SERIALIZED_NOP, this->DESERIALIZED_NOP);

    return result;
}