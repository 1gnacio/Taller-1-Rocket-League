//
// Created by ignacio on 04/11/22.
//

#ifndef ROCKET_LEAGUE_RESPONSE_QUEUE_H
#define ROCKET_LEAGUE_RESPONSE_QUEUE_H

#include <queue>
#include "../protocolo/responses/response.h"
#include "../protocolo/protocolo.h"

class ResponseQueue {
private:
    std::queue<Response> responses;
public:
    ResponseQueue();

    void push(Response& response);

    Response pop();
};


#endif //ROCKET_LEAGUE_RESPONSE_QUEUE_H
