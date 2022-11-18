#include "response_blocking_queue.h"

void ResponseBlockingQueue::push(Response &response) {
    std::unique_lock<std::mutex> lock(mutex);
    this->responses.push(response);
    cv.notify_all();
}

Response ResponseBlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while(this->responses.empty()) {
        cv.wait(lock);
    }
    Response element = this->responses.front();
    this->responses.pop();
    return element;
}