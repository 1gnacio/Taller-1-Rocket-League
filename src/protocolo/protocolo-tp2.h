#ifndef __CLIENT_PROTOCOLO_H__
#define __CLIENT_PROTOCOLO_H__

#include <iostream>
#include <string>
#include <vector>
#include "../sockets/socket.h"

class ClientProtocolo {
private:
    Socket socket;
    bool was_closed;
public:
    ClientProtocolo(const char *hostname, const char *port);
    bool isRunning();
    void sendActions(std::string message);
    std::string receiveResponse();
    ~ClientProtocolo() = default;
};

#endif //__CLIENT_PROTOCOLO_H__
