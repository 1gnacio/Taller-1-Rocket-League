#ifndef CLIENT_H
#define CLIENT_H

#include "../handlers/server_connection.h"
#include "sdl_main.h"

class Client {
private:
    bool isRunning;
    ServerConnection connection;
    sdl_main sdl_handler;
    void readStandardInput();
    void addInputCommand(std::string deserialized_key);
public:
    Client(const char *hostname, const char *servname);
    void run();
};

#endif  // CLIENT_H
