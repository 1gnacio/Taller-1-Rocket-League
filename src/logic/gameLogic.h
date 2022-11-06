#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include "boxLogic.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"

class GameLogic {
private:
    BoxLogic gamePhysics;

public:
    GameLogic();
    void update(Command &command);
    void update();
    Response getResponse();
};


#endif //ROCKET_LEAGUE_LOGICGAME_H
