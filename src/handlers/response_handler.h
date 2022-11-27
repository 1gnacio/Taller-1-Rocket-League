#ifndef RECEIVE_RESPONSE_HANDLER_H
#define RECEIVE_RESPONSE_HANDLER_H

#include <thread>
#include "../sockets/socket.h"
#include "../protocolo/protocolo.h"
#include "../queues/response_queue.h"
#include "enums/mode.h"
#include "id_service.h"

class ResponseHandler {
private:
    ResponseQueue& queue;
    Socket& socket;
    IdService& idService;
    bool hasFinished;
    Protocolo protocolo;
    std::thread handler;

    void handleReceive();
    void handleSend();

public:
    ResponseHandler(Socket& socket, IdService &idService,  ResponseQueue &queue, Mode mode);

    void push(Response& response);

    Response pop();

    void stopHandler();

    bool isFinished();

    ~ResponseHandler();

    void clearResponses();
};


#endif // RECEIVE_RESPONSE_HANDLER_H
