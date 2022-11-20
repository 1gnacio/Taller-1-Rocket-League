#ifndef GAME_MODEL_LOGIC_H
#define GAME_MODEL_LOGIC_H

#include <vector>
#include "gameLogic.h"
#include "../constants/command_values.h"

class GameModelLogic {
private:
    std::vector<std::unique_ptr<GameLogic>> gamesLogic;
    CommandValues commands;
    std::vector<std::string> actionCommands;
    std::vector<std::string> movementCommands;

    void applyMatchLogic(Command &command);
public:
    GameModelLogic();
    void updateModel(Command &command);
    Response getResponse();
    void updateTime();

};


#endif // GAME_MODEL_LOGIC_H
