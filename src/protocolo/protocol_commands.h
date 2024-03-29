#ifndef PROTOCOL_COMMANDS_H
#define PROTOCOL_COMMANDS_H

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
public:
    ProtocolCommands();

    std::string getDeserializedCommandValue(unsigned char serialized);

    Command createCommand(int id, std::string& value);

    Command createCommand(int id, std::string& value, std::string &firstParameter);

    Command createCommand(int id, std::string& value, std::string &firstParameter, std::string &secondParameter);

};


#endif // PROTOCOL_COMMANDS_H
