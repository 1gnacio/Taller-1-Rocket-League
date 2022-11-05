#include <algorithm>
#include "send_response_handler.h"

SendResponseHandler::SendResponseHandler() : hasFinished(false), handlers(), queue() {}

void SendResponseHandler::addPlayer(Socket &socket) {
    this->handlers.push_back(std::make_unique<ResponseHandler>(socket, queue, SENDER));
}

void SendResponseHandler::push(Response &response) {
    this->queue.push(response);
}

void SendResponseHandler::stopHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;

        for(auto& handler : this->handlers) {
            handler->stopHandler();
        }
    }
}

bool waitIfFinished(std::unique_ptr<ResponseHandler>& handler) {
    return handler->isFinished();
}

void SendResponseHandler::cleanFinishedHandlers() {
    this->handlers.erase(std::remove_if(this->handlers.begin(),
                                        this->handlers.end(),
                                        waitIfFinished),
                         this->handlers.end());
}

SendResponseHandler::~SendResponseHandler() {
    this->hasFinished = true;

    for (auto& handler : handlers) {
        handler->stopHandler();
    }
}

