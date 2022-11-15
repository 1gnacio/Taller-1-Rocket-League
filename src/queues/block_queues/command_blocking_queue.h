#ifndef COMMAND_BLOCKING_QUEUE_H
#define COMMAND_BLOCKING_QUEUE_H

#include <condition_variable>
#include "../src/queues/command_queue.h"

class CommandBlockingQueue : public CommandQueue {
private:
    std::queue<Command> commands;
    std::mutex mutex;
    std::condition_variable cv; // tiene elementos?
public:
    void push(Command &element);

    Command pop();
};


#endif // COMMAND_BLOCKING_QUEUE_H
