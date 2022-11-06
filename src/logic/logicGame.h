#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include "logicBox.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"

class LogicGame {
private:
    LogicBox gamePhysics;

public:
    LogicGame();
    void createResponse(Command command);


};


#endif //ROCKET_LEAGUE_LOGICGAME_H
