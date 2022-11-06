#ifndef SERVER_ENDPOINT_H
#define SERVER_ENDPOINT_H

#include <vector>
#include "client_connection.h"

class ServerEndpoint {
private:
    bool isActive;
    CommandQueue receivedCommands;
    ResponseQueue responses;
    std::vector<std::unique_ptr<ClientConnection>> connections;
    std::thread sender;

    void sendResponsesHandler();
public:
    ServerEndpoint();

    void addPlayer(Socket& client);

    void push(Response& response);

    Command pop();

    void cleanFinishedConnections();

    void stopConnections();

    ~ServerEndpoint();
};


#endif // SERVER_ENDPOINT_H