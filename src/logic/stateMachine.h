#ifndef ROCKET_LEAGUE_STATEMACHINE_H
#define ROCKET_LEAGUE_STATEMACHINE_H

#include <string>
#include "boxLogic.h"
#include "../protocolo/commands/command.h"
/*
 * Clase que resuelve la logica del tipo de movimiento
 * que debe realizarse a partir de los datos que le llegan.
 */


class stateMachine {

    std::string defineDoubleJump(Command &command);

};


#endif //ROCKET_LEAGUE_STATEMACHINE_H
