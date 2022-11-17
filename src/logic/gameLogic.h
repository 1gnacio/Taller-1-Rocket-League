#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include "boxLogic.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"
#include "game.h"

class GameLogic {
private:
    BoxLogic gamePhysics;
    //GameInfo info --> Que tenga los goles de cada equipo y el tiempo
    Game game;

public:
    GameLogic();
    bool withoutPlayers;
    void updateModel(Command &command);
    void updateTime();
    Response getResponse();

    float getCarData(int carNumber, int key);

    float playersAmount();
};


#endif //ROCKET_LEAGUE_LOGICGAME_H
