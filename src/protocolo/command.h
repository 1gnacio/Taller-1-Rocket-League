//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_COMMAND_H
#define TALLER_1_ROCKET_LEAGUE_COMMAND_H

#include <string>

class Command {
private:
    const char serialized;
    const std::string deserialized;
    const std::string parameters;
public:
    Command(const char serialized, const std::string& deserialized);
    Command(const char serialized, const std::string& deserialized, const std::string& parameters);
    char serialize();
    Command(Command&&);
    Command& operator=(Command&&);
};


#endif //TALLER_1_ROCKET_LEAGUE_COMMAND_H
