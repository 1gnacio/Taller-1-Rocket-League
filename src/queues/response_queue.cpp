#include "response_queue.h"

ResponseQueue::ResponseQueue() : responses(), protocolo() {}

void ResponseQueue::push(Response &response) {
    responses.push(response);
}

Response ResponseQueue::pop() {
    if (!this->responses.empty()) {
        Response r = responses.front();
        responses.pop();
        return r;
    }

    return Response()
}