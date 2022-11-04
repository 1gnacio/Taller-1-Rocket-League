#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H

#include "logicGame.h"
#include <queue>
#include <vector>


class Game {
private:
    LogicGame logic;
    std::queue<std::byte> inputQueue;
    std::queue<std::byte> answerQueue;

    void removeLastCommand();
public:
    Game();
    int startGame();
    void updateModel();
    void addCommand(std::byte);
    int numberOfCommand();
};


#endif //ROCKET_LEAGUE_GAME_H
