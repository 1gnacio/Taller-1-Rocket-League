#ifndef CONNECTION_HELPER_H
#define CONNECTION_HELPER_H

#include <thread>
#include <atomic>
#include "../sockets/socket.h"

class ConnectionHelper {
private:
    std::atomic<bool> hasFinished;
    std::thread idManager;
    std::atomic<int> id;
    void receiveId(Socket &socket);
    void sendId(Socket &socket);

public:
    ConnectionHelper(Socket &socket, int id);
    explicit ConnectionHelper(Socket &socket);
    bool isFinished() { return this->hasFinished; };
    void awaitHelper();
    ~ConnectionHelper();

    [[nodiscard]] int getId() const { return this->id; };
};


#endif // CONNECTION_HELPER_H
