//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
#define TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H

#include <map>
#include <string>
#include <vector>
#include "command.h"
#include "../constants/command_values.h"

class ProtocolCommands {
private:
    CommandValues values;
    std::map<const char, const std::string> deserializedCommands;
    std::map<const std::string, const char> serializedCommands;
public:
    ProtocolCommands();

    Command createMovementCommand(std::string& value);
    Command createMovementCommand(const char value);

    std::vector<Command> createCommandSequence(std::vector<std::string>& receivedInput);


};


#endif //TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
