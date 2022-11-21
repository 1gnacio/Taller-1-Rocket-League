#ifndef SERVER_ENDPOINT_H
#define SERVER_ENDPOINT_H

#include <vector>
#include "client_connection.h"
#include "../src/queues/block_queues/response_blocking_queue.h"
#include "../src/queues/block_queues/command_blocking_queue.h"

class ServerEndpoint {
private:
    bool isActive;
    int nextClientId = 1;
    CommandBlockingQueue receivedCommands;
    ResponseBlockingQueue responses;
    std::vector<std::unique_ptr<ClientConnection>> connections;
    std::thread sender;

    void sendResponsesHandler();
public:
    ServerEndpoint();

    void addPlayer(Socket& client);

    void push(Response response);

    Command pop();

    bool queueEmpty();

    void cleanFinishedConnections();

    void stopConnections();

    ~ServerEndpoint();
};


#endif // SERVER_ENDPOINT_H
