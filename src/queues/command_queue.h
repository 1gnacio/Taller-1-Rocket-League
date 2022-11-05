//
// Created by ignacio on 04/11/22.
//

#ifndef ROCKET_LEAGUE_COMMAND_QUEUE_H
#define ROCKET_LEAGUE_COMMAND_QUEUE_H

#include <queue>
#include "../protocolo/commands/command.h"
#include "../protocolo/protocolo.h"

class CommandQueue {
private:
    std::queue<Command> commands;
public:
    CommandQueue();

    void push(Command& command);

    Command pop();
};


#endif //ROCKET_LEAGUE_COMMAND_QUEUE_H
