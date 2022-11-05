#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "../queues/command_queue.h"
#include "../queues/response_queue.h"
#include "../sockets/socket.h"
#include "../handlers/command_handler.h"
#include "../handlers/response_handler.h"

class ServerConnection {
private:
    bool isConnected;
    Socket socket;
    CommandQueue commandQueue;
    CommandHandler sender;
    ResponseHandler receiver;
public:
    ServerConnection(Socket& socket);

    void push(Command& command);

    Response pop();

    bool connectionClosed();

    void closeConnection();

    ~ServerConnection();
};


#endif // SERVER_CONNECTION_H
