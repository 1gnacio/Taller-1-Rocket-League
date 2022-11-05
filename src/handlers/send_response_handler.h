#ifndef SEND_RESPONSE_HANDLER_H
#define SEND_RESPONSE_HANDLER_H

#include <thread>
#include <vector>
#include "response_handler.h"

class SendResponseHandler {
private:
    bool hasFinished;
    ResponseQueue queue;
    std::vector<std::unique_ptr<ResponseHandler>> handlers;

public:
    SendResponseHandler();

    void addPlayer(Socket& socket);

    void push(Response& response);

    void stopHandler();

    void cleanFinishedHandlers();

    //TODO remove player?

    ~SendResponseHandler();
};


#endif // SEND_RESPONSE_HANDLER_H
