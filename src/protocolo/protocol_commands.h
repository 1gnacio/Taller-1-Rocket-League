//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
#define TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H

#include <map>
#include <string>
#include <vector>
#include "commands/command.h"
#include "../constants/command_values.h"
#include "../protocolo/commands/strategies/base_parameter_strategy.h"

class ProtocolCommands {
private:
    CommandValues values;
    std::map<const char, const std::string> deserializedCommands;
    std::map<const std::string, const char> serializedCommands;
    std::vector<std::string> parameteredCommands;

    Command createSimpleCommand(const char serialized,
                                const std::string& deserialized) const;

    Command createParameteredCommand(const char serialized,
                                     const std::string& deserialized,
                                     std::string &arguments);
public:
    ProtocolCommands();

    Command createCommand(std::string& value);

    Command createCommand(std::vector<char> serializedCommand);

};


#endif //TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
