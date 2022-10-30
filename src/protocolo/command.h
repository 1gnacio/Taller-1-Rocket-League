//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_COMMAND_H
#define TALLER_1_ROCKET_LEAGUE_COMMAND_H

#include <string>

class Command {
private:
    char serialized;
    std::string deserialized;
public:
    Command(char serialized, std::string& deserialized);
    std::string serialize();
};


#endif //TALLER_1_ROCKET_LEAGUE_COMMAND_H
