#include "response_queue.h"

ResponseQueue::ResponseQueue() : responses() {}

void ResponseQueue::push(Response &response) {
    std::lock_guard<std::mutex> l(this->mutex);
    responses.push(response);
}

Response ResponseQueue::pop() {
    std::lock_guard<std::mutex> l(this->mutex);
    if (!this->responses.empty()) {
        Response r = responses.front();
        responses.pop();
        return r;
    }

    return {};
}