#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <memory>
#include <vector>
#include "../sockets/socket.h"
#include "../handlers/server_endpoint.h"
#include "../logic/gameLogic.h"
#include "../game_model/game_model.h"

class Server {
private:
    Socket accepter;
    ServerEndpoint endpoint;
    std::atomic<bool> isClosed;
    GameModel gameModel;

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


    void lobbyThread();
};


#endif  // SERVER_H
