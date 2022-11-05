#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <queue>
#include <mutex>
#include "../protocolo/commands/command.h"
#include "../protocolo/protocolo.h"

class CommandQueue {
private:
    std::mutex mutex;
    std::queue<Command> commands;
public:
    CommandQueue();

    void push(Command& command);

    Command pop();
};

#endif // COMMAND_QUEUE_H
