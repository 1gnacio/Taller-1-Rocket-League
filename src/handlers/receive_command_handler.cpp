#include <algorithm>
#include "receive_command_handler.h"

ReceiveCommandHandler::ReceiveCommandHandler() :
hasFinished(false),
queue(),
handlers()
{}

void ReceiveCommandHandler::stopHandler() {
    if (this->hasFinished) {
        this->hasFinished = true;
    }
}

Command ReceiveCommandHandler::pop() {
    return this->queue.pop();
}

void ReceiveCommandHandler::addPlayer(Socket &socket) {
    this->handlers.push_back(std::make_unique<CommandHandler>(socket, queue, RECEIVER));
}

bool waitIfFinished(std::unique_ptr<CommandHandler>& handler) {
    return handler->isFinished();
}

void ReceiveCommandHandler::cleanFinishedHandlers() {
    this->handlers.erase(std::remove_if(this->handlers.begin(),
                                        this->handlers.end(),
                                        waitIfFinished),
                         this->handlers.end());
}

ReceiveCommandHandler::~ReceiveCommandHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
        for (auto& handler : this->handlers) {
            handler->stopHandler();
        }
    }
}