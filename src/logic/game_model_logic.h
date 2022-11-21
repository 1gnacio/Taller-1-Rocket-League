#ifndef GAME_MODEL_LOGIC_H
#define GAME_MODEL_LOGIC_H

#include <vector>
#include "gameLogic.h"
#include "../constants/command_values.h"

class GameModelLogic {
private:
    std::mutex mutex;
    std::vector<std::unique_ptr<GameLogic>> gamesLogic;
    CommandValues commands;
    std::vector<std::string> actionCommands;
    std::vector<std::string> movementCommands;

    void applyMatchAction(Command &command);
public:
    GameModelLogic();
    void updateModel(Command &command);
    MatchResponses getResponses();

    void updateTime();
};


#endif // GAME_MODEL_LOGIC_H
