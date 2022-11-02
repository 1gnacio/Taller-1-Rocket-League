//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_COMMAND_H
#define TALLER_1_ROCKET_LEAGUE_COMMAND_H

#include <string>
#include "strategies/base_parameter_strategy.h"

class Command {
private:
    char serialized;
    std::string deserialized;
    std::string firstParameter;
    std::string secondParameter;
public:
    // movimientos, acciones, listar
    Command(const char serialized,
            const std::string& deserialized);

    // unirse
    Command(const char serialized,
            const std::string& deserialized,
            const std::string &firstParameter);

    // crear
    Command(const char serialized,
            const std::string& deserialized,
            const std::string& firstParameter,
            const std::string& secondParameter);

    char serialize();

    // hago los comandos movibles
    Command(Command&&);
    Command& operator=(Command&&);
};


#endif //TALLER_1_ROCKET_LEAGUE_COMMAND_H
