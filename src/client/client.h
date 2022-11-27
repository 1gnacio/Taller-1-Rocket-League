#ifndef __CLIENT_CLIENT_H
#define __CLIENT_CLIENT_H

#include "../handlers/server_connection.h"
#include "sdl_main.h"

class Client {
private:
    bool isRunning;
    ServerConnection& connection;
    sdl_main sdl_handler;
    void readStandardInput();
    void addInputCommand(std::string deserialized_key);
    void quitMatch();
public:
    explicit Client(ServerConnection& connection);
    ~Client() = default;
    void run();
};

#endif  // __CLIENT_CLIENT_H
