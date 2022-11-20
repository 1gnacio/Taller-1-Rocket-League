#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H

#include <queue>
#include <mutex>
#include "../protocolo/commands/command.h"
#include "../protocolo/protocolo.h"

class CommandQueue {
protected:
    std::mutex mutex;
    std::queue<Command> commands;
public:
    CommandQueue();

    virtual void push(Command& command);

    virtual Command pop();
};

#endif // COMMAND_QUEUE_H
