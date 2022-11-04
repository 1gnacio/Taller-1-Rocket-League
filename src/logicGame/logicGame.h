#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include <queue>

class LogicGame {
public:

    LogicGame();
    void update(std::queue<std::byte> &queue);
    void clearQueue(std::queue<std::byte> &queue);
};
#endif //ROCKET_LEAGUE_LOGICGAME_H

