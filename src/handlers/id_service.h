#ifndef ID_RECEIVER_THREAD_H
#define ID_RECEIVER_THREAD_H

#include <atomic>
#include "enums/mode.h"
#include "../src/sockets/socket.h"

class IdService {
private:
    Mode mode;
    Socket &socket;
    std::atomic<int> id;

    void sendId();
    void receiveId();

public:
    void run();
    IdService(Mode mode, Socket &socket, int id);
    [[nodiscard]] int getId() const {return this->id;};
};


#endif // ID_RECEIVER_THREAD_H
