#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <memory>
#include <vector>
#include "../sockets/socket.h"
#include "../game_model/game_model_monitor.h"
#include "../handlers/server_endpoint.h"
#include "../logic/gameLogic.h"
#include "../src/logic/game_model_logic.h"

class Server {
private:
    std::atomic<bool> isClosed = false;
    GameModelMonitor monitor;

    GameModelLogic logic;
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
