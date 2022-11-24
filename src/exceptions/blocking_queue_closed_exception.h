#ifndef BLOCKING_QUEUE_CLOSED_EXCEPTION_H
#define BLOCKING_QUEUE_CLOSED_EXCEPTION_H

#include <exception>

class BlockingQueueClosedException : public std::exception {
public:
    explicit BlockingQueueClosedException() = default;

    const char * what() {
        return "Queue has closed";
    }
};

#endif // BLOCKING_QUEUE_CLOSED_EXCEPTION_H