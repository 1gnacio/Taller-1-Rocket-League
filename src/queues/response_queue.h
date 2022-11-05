#ifndef RESPONSE_QUEUE_H
#define RESPONSE_QUEUE_H

#include <queue>
#include <mutex>
#include "../protocolo/responses/response.h"
#include "../protocolo/protocolo.h"

class ResponseQueue {
private:
    std::mutex mutex;
    std::queue<Response> responses;
public:
    ResponseQueue();

    void push(Response& response);

    Response pop();
};


#endif // RESPONSE_QUEUE_H
