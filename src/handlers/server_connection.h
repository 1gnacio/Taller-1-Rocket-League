#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include "../sockets/socket.h"
#include "../handlers/command_handler.h"
#include "../handlers/response_handler.h"
#include "../queues/block_queues/response_blocking_queue.h"
#include "../queues/block_queues/command_blocking_queue.h"
#include "../protocolo/connection_helper.h"

class ServerConnection {
private:
    bool isConnected;
    Socket socket;
    ConnectionHelper helper;
    CommandBlockingQueue commandQueue;
    ResponseBlockingQueue responseQueue;
    CommandHandler sender;
    ResponseHandler receiver;
public:
    ServerConnection(const char *hostname, const char *servname);

    void push(Command& command);

    Response pop();

    bool connectionClosed();

    void closeConnection();

    [[nodiscard]] int getId() const { return this->helper.getId(); }

    ~ServerConnection();
};


#endif // SERVER_CONNECTION_H
