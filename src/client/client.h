#ifndef CLIENT_H
#define CLIENT_H

#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"
#include "../sockets/socket.h"
#include "../handlers/command_handler.h"
#include "../handlers/response_handler.h"

class Client {
private:
    bool isRunning;
    Socket socket;
    CommandQueue cQueue;
    ResponseQueue rQueue;
    CommandHandler senderHandler;
    ResponseHandler receiverHandler;

    void resolveResponse(const Command& sentCommand, const Response& response);
    void readStandardInput();
public:
    Client(const char *hostname, const char *servname);
    void run();
};

#endif  // CLIENT_H
