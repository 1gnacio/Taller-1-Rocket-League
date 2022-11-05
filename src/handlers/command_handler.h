#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <thread>
#include "../queues/command_queue.h"

enum Mode {
    RECEIVER,
    SENDER
};

class CommandHandler {
private:
    bool hasFinished;
    CommandQueue& queue;
    Protocolo protocolo;
    Socket& socket;
    std::thread handler;

    void handleSend();

    void handleReceive();
public:
    CommandHandler(Socket& socket, CommandQueue& queue, Mode mode);

    void push(Command& command);

    Command pop();

    void stopHandler();

    bool isFinished();

    ~CommandHandler();
};


#endif // COMMAND_HANDLER_H
