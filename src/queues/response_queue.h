#ifndef RESPONSE_QUEUE_H
#define RESPONSE_QUEUE_H

#include <queue>
#include <mutex>
#include "../protocolo/responses/response.h"
#include "../protocolo/protocolo.h"

class ResponseQueue {
protected:
    std::mutex mutex;
    std::queue<Response> responses;
public:
    ResponseQueue();

    virtual void push(Response& response);

    virtual Response pop();
};


#endif // RESPONSE_QUEUE_H
