#ifndef CLIENT_H
#define CLIENT_H

#include "../common_src/command.h"
#include "../common_src/response.h"

class Client {
private:
    void resolveResponse(const Command& sentCommand, const Response& response);
public:
    void run(const char *hostname, const char *servname);
};

#endif  // CLIENT_H
