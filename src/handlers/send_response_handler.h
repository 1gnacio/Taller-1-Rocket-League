//
// Created by ignacio on 04/11/22.
//

#ifndef ROCKET_LEAGUE_SEND_RESPONSE_HANDLER_H
#define ROCKET_LEAGUE_SEND_RESPONSE_HANDLER_H

#include <thread>
#include <vector>
#include "response_handler.h"

class SendResponseHandler {
private:
    bool hasFinished;
    ResponseQueue queue;
    std::vector<std::unique_ptr<ResponseHandler>> handlers;
    std::thread sender;

    void sendResponse();

public:
    SendResponseHandler();

    void addPlayer(Socket& socket);

    void push(Response& response);

    void stopHandler();

    //TODO remove player?

    ~SendResponseHandler();
};


#endif //ROCKET_LEAGUE_SEND_RESPONSE_HANDLER_H
