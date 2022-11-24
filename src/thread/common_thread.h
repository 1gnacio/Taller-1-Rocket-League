#ifndef _COMMON_THREAD_H
#define _COMMON_THREAD_H

#include <iostream>
#include <thread>

/**
 * @brief      Abstract class wrapping a thread. It catches exceptions in order
 *             to avoid crashes with confusing messages.
 *
 *             User should extend this class and implement the run() method with
 *             the behavior to be executed in a new thread.
 */
class Thread {
private:
    std::thread t;
    bool done = false;

    // This template method catches exceptions (they can't be caught from main)
    void runExpecting();

protected:
    virtual void run() = 0;

public:
    /**
     * @brief      Starts a thread with the behavior of the method run().
     */
    void start();

    /**
     * @brief      Waits the thread to finish.
     */
    void join();
    bool hasFinished();
    virtual ~Thread() = default;
};

#endif //_COMMON_THREAD_H
