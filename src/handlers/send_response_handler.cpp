#include "send_response_handler.h"

SendResponseHandler::SendResponseHandler() : hasFinished(false), handlers(), queue(),
sender(std::thread(&SendResponseHandler::sendResponse, this)) {}

void SendResponseHandler::addPlayer(Socket &socket) {
    this->handlers.push_back(std::make_unique<ResponseHandler>(socket, SENDER));
}

void SendResponseHandler::sendResponse() {
    if (!this->hasFinished) {
        Response r = this->queue.pop();

        for(auto& handler : handlers) {
            handler->push(r);
        }
    }
}

void SendResponseHandler::push(Response &response) {
    this->queue.push(response);
}

SendResponseHandler::~SendResponseHandler() {
    this->hasFinished = true;

    for (auto& handler : handlers) {
        handler->stopHandler();
    }

    this->sender.join();
}
