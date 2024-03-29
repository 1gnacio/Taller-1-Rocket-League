#ifndef COMMAND_BLOCKING_QUEUE_H
#define COMMAND_BLOCKING_QUEUE_H

#include <condition_variable>
#include "../src/queues/command_queue.h"

class CommandBlockingQueue : public CommandQueue {
private:
    std::condition_variable cv; // tiene elementos?
    bool isClosed;
public:
    void push(Command &element);

    Command pop();

    void close();
};


#endif // COMMAND_BLOCKING_QUEUE_H
