//
// Created by ignacio on 02/10/22.
//

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <thread>
#include <atomic>
#include "../common_src/command.h"
#include "../common_src/response.h"
#include "../common_src/socket.h"
#include "game_model_monitor.h"

class ClientHandler {
private:
    std::atomic<bool> hasFinished;
    Socket client;
    GameModelMonitor& monitor;
    std::thread thread;

    void handle();
public:
    explicit ClientHandler(Socket& client, GameModelMonitor& monitor);

    void stopHandler();

    bool finished();

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

    ~ClientHandler();
};


#endif // CLIENT_HANDLER_H
