#ifndef CLIENT_H
#define CLIENT_H

#include "../sockets/socket.h"
#include "../handlers/server_connection.h"

class Client {
private:
    bool isRunning;
    Socket socket;
    ServerConnection connection;

    void resolveResponse(const Command& sentCommand, const Response& response);
    void readStandardInput();
public:
    Client(const char *hostname, const char *servname);
    void run();
};

#endif  // CLIENT_H
