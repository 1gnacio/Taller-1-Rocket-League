#ifndef RESPONSEBLOCKINGQUEUE_H
#define RESPONSEBLOCKINGQUEUE_H

#include <condition_variable>
#include "../src/queues/response_queue.h"

class ResponseBlockingQueue : public ResponseQueue {
private:
    std::condition_variable cv; // tiene elementos?
public:
    void push(Response &element);

    Response pop();
};


#endif // RESPONSEBLOCKINGQUEUE_H
