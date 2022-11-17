#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../sockets/socket.h"
#include "command_handler.h"
#include "response_handler.h"
#include "../protocolo/connection_helper.h"

class ClientConnection {
private:
    bool isClosed;
    // el servidor necesita guardar el socket del cliente en algun lado, por el momento aca
    Socket socket;
    ConnectionHelper helper;
    CommandHandler receiver;
    ResponseHandler sender;
public:
    ClientConnection(int id, Socket& socket, ResponseQueue &responseQueue, CommandQueue& queue);

    void push(Response& response);

    void closeConnection();

    bool connectionClosed();

    [[nodiscard]] int getId() const { return this->helper.getId(); }

    ~ClientConnection();
};


#endif // CLIENT_CONNECTION_H
