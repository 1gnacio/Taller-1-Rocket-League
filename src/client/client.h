#ifndef CLIENT_H
#define CLIENT_H

#include "../handlers/server_connection.h"
#include "sdl_main.h"
#include "../lobby/lobby.h"
#include <QApplication>
class Client {
private:
    bool isRunning;
    ServerConnection connection;
    sdl_main sdl_handler;
    //lobby my_lobby;
    void readStandardInput();
    void addInputCommand(std::string deserialized_key);
public:
    Client(const char *hostname, const char *servname);
    ~Client() = default;
    void run();
    //int runLobby();
};

#endif  // CLIENT_H
