#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include "../sockets/socket.h"
#include "command_handler.h"
#include "response_handler.h"

class ClientConnection {
private:
    bool isClosed;
    // el servidor necesita guardar el socket del cliente en algun lado, por el momento aca
    Socket socket;
    CommandHandler receiver;
    ResponseHandler sender;
public:
    ClientConnection(Socket& socket, CommandQueue& queue);

    void push(Response& response);

    void closeConnection();

    bool connectionClosed();

    ~ClientConnection();
};


#endif // CLIENT_CONNECTION_H
