#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include "boxLogic.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"

class GameLogic {
private:
    BoxLogic gamePhysics;
    //GameInfo info --> Que tenga los goles de cada equipo y el tiempo

public:
    GameLogic();
    bool withoutPlayers;
    void updateModel(Command &command);
    void updateTime();
    Response getResponse();
};


#endif //ROCKET_LEAGUE_LOGICGAME_H
