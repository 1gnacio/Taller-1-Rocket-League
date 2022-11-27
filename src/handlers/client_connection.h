#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../sockets/socket.h"
#include "command_handler.h"
#include "response_handler.h"
#include "../queues/block_queues/response_blocking_queue.h"
#include "../queues/block_queues/command_blocking_queue.h"

class ClientConnection {
private:
    bool isClosed;
    // el servidor necesita guardar el socket del cliente en algun lado, por el momento aca
    Socket socket;
    IdService idService;
    CommandQueue& commandQueue;
    ResponseBlockingQueue responseQueue;
    CommandHandler receiver;
    ResponseHandler sender;
public:
    ClientConnection(int id, CommandQueue &queue, Socket& socket);

    void push(Response& response);

    void closeConnection();

    bool connectionClosed();

    [[nodiscard]] int getId() { return this->idService.getId(); }

    ~ClientConnection();
};


#endif // CLIENT_CONNECTION_H
