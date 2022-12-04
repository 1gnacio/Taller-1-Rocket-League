#include "response_blocking_queue.h"
#include "../src/exceptions/blocking_queue_closed_exception.h"

void ResponseBlockingQueue::push(Response &response) {
    std::unique_lock<std::mutex> lock(mutex);
    this->responses.push(response);
    cv.notify_all();
}

Response ResponseBlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while(this->isClosed || this->responses.empty()) {
        if (this->isClosed) {
            throw BlockingQueueClosedException();
        }
        cv.wait(lock);
    }
    Response element = std::move(this->responses.front());
    this->responses.pop();
    return std::move(element);
}

void ResponseBlockingQueue::close() {
    std::unique_lock<std::mutex> lock(mutex);
    isClosed = true;
    cv.notify_all();
}

ResponseBlockingQueue::ResponseBlockingQueue() : cv(), isClosed(false) {}
