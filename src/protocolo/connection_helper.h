#ifndef CONNECTION_HELPER_H
#define CONNECTION_HELPER_H

#include "../sockets/socket.h"

class ConnectionHelper {
private:
    int id;
    int receiveId(Socket &socket);
    void sendId(Socket &socket);
public:
    ConnectionHelper(Socket &socket, int id);
    explicit ConnectionHelper(Socket &socket);

    [[nodiscard]] int getId() const { return this->id; };
};


#endif // CONNECTION_HELPER_H
