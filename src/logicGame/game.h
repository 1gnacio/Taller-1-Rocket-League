#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H

#include "logicGame.h"
#include <queue>
#include <vector>
#include "../protocolo/commands/command.h"


class Game {
private:
    LogicGame logic;
    std::queue<Command> inputQueue;
    std::queue<Command> answerQueue;

    void removeLastCommand();
public:
    Game();
    int startGame();
    void updateModel();
    void addCommand(Command);
    int numberOfCommand();
};


#endif //ROCKET_LEAGUE_GAME_H
