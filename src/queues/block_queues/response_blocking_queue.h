#ifndef RESPONSEBLOCKINGQUEUE_H
#define RESPONSEBLOCKINGQUEUE_H

#include <condition_variable>
#include "../src/queues/response_queue.h"

class ResponseBlockingQueue : public ResponseQueue {
private:
    std::condition_variable cv; // tiene elementos?
    bool isClosed;
public:
    ResponseBlockingQueue();

    void push(Response &element) override;

    Response pop() override;

    void close();
};


#endif // RESPONSEBLOCKINGQUEUE_H