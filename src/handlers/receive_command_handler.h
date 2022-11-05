#ifndef RECEIVE_COMMANDS_HANDLER_H
#define RECEIVE_COMMANDS_HANDLER_H

#include <vector>
#include "command_handler.h"

class ReceiveCommandHandler {
private:
    bool hasFinished;
    CommandQueue queue;
    std::vector<std::unique_ptr<CommandHandler>> handlers;

public:
    ReceiveCommandHandler();

    void addPlayer(Socket& socket);

    Command pop();

    void stopHandler();

    void cleanFinishedHandlers();

    //TODO remove player?

    ~ReceiveCommandHandler();
};


#endif // RECEIVE_COMMANDS_HANDLER_H
