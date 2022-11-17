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

class ProtocolCommands {
private:
    CommandValues values;
    std::map<const unsigned char, const std::string> deserializedCommands;
    std::map<const std::string, const unsigned char> serializedCommands;
    std::vector<std::string> parameteredCommands;

    [[nodiscard]] Command createSimpleCommand(int id, unsigned char serialized,
                                const std::string& deserialized) const;

    Command createParameteredCommand(int id, unsigned char serialized,
                                     const std::string& deserialized,
                                     std::string &arguments);
public:
    ProtocolCommands();

    Command createCommand(int id, std::string& value);

    std::string getDeserializedCommandValue(unsigned char serializedCommandValue);

    Command createCommand(std::vector<unsigned char> &serializedCommand);

};


#endif //TALLER_1_ROCKET_LEAGUE_PROTOCOL_COMMANDS_H
