#ifndef ROCKET_LEAGUE_LOGICGAME_H
#define ROCKET_LEAGUE_LOGICGAME_H

#include <queue>
#include "../protocolo/commands/command.h"
class LogicGame {
public:

    LogicGame();
    void update(std::queue<Command> &queue);
    void clearQueue(std::queue<Command> &queue);
};
#endif //ROCKET_LEAGUE_LOGICGAME_H

