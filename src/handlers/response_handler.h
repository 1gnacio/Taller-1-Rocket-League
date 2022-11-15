#ifndef RECEIVE_RESPONSE_HANDLER_H
#define RECEIVE_RESPONSE_HANDLER_H

#include <thread>
#include "../sockets/socket.h"
#include "../protocolo/protocolo.h"
#include "../queues/response_queue.h"
#include "enums/mode.h"

class ResponseHandler {
private:
    ResponseQueue& queue;
    Socket& socket;
    bool hasFinished;
    Protocolo protocolo;
    std::thread handler;

    void handleReceive();
    void handleSend();

public:
    ResponseHandler(Socket& socket, ResponseQueue &queue, Mode mode);

    void push(Response& response);

    Response pop();

    void stopHandler();

    bool isFinished();

    ~ResponseHandler();
};


#endif // RECEIVE_RESPONSE_HANDLER_H
