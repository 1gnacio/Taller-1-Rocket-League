#include "command_blocking_queue.h"
#include "../src/exceptions/blocking_queue_closed_exception.h"

void CommandBlockingQueue::push(Command &element) {
    std::unique_lock<std::mutex> lock(mutex);
    this->commands.push(std::move(element));
    cv.notify_all();
}

Command CommandBlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while(this->isClosed || this->commands.empty()) {
        if (this->isClosed) {
            throw BlockingQueueClosedException();
        }
        cv.wait(lock);
    }
    Command element = std::move(this->commands.front());
    this->commands.pop();
    return element;
}

void CommandBlockingQueue::close() {
    std::unique_lock<std::mutex> lock(mutex);
    isClosed = true;
    cv.notify_all();
}