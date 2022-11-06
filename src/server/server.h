#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <memory>
#include <vector>
#include "../sockets/socket.h"
#include "../game_model/game_model_monitor.h"
#include "../handlers/server_endpoint.h"
#include "../logic/gameLogic.h"

class Server {
private:
    std::atomic<bool> isClosed = false;
    GameModelMonitor monitor;

    GameLogic logic; // No hace falta monitor porque lee de una cola
    Socket accepter;
    ServerEndpoint endpoint;

    Socket acceptClient();

    void acceptClients();

    void startHandler(Socket& client);

    void cleanFinishedHandlers();

    void stopHandlers();

public:
    explicit Server(const char* servname);
    void run();
    void gameFlow();

    // hago el servidor no copiable
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

    ~Server();


};


#endif  // SERVER_H
