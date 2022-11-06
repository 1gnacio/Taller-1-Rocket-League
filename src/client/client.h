#ifndef CLIENT_H
#define CLIENT_H

#include "../handlers/server_connection.h"

class Client {
private:
    bool isRunning;
    ServerConnection connection;

    void readStandardInput();
public:
    Client(const char *hostname, const char *servname);
    void run();
};

#endif  // CLIENT_H
