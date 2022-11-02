#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <memory>
#include <vector>
#include "../common_src/socket.h"
#include "../common_src/command.h"
#include "../common_src/protocolo.h"
#include "game_model_monitor.h"
#include "client_handler.h"


class Server {
private:
    std::atomic<bool> isClosed = false;
    GameModelMonitor monitor;
    Socket accepter;
    std::vector<std::unique_ptr<ClientHandler>> clientHandlers;

    Socket acceptClient();

    void acceptClients();

    void startHandler(Socket& client);

    void cleanFinishedHandlers();

    void stopHandlers();

public:
    explicit Server(const char* servname);
    void run();

    // hago el servidor no copiable
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    ~Server();
};


#endif  // SERVER_H
