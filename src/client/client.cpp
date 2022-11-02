#include <iostream>
#include <string>
#include "client.h"
#include "../sockets/socket.h"
#include "../protocolo/protocolo.h"

void Client::run(const char *hostname, const char *servname) {
    Socket socket(hostname, servname);

    Protocolo protocolo;

    std::string input;

    while (!protocolo.isConnectionClosed()
            && std::getline(std::cin, input)
            && input != "fin") {
        Command sentCommand = protocolo.createCommand(input);

        protocolo.sendCommand(socket, sentCommand);

        Response response = protocolo.receiveResponse(socket);

        this->resolveResponse(sentCommand, response);
    }
}

void Client::resolveResponse(const Command& sentCommand, const Response& response) {
    AvailableCommands commands;
    bool statusOk = response.getStatus() == "OK";
    std::string result;

    if (sentCommand.getValue() == commands.createValue) {
        result = statusOk ? "Creación exitosa" : "Creación fallida";
    } else if (sentCommand.getValue() == commands.joinValue) {
        result = statusOk ? "Unión exitosa" : "Unión fallida";
    }

    if (!result.empty()) {
        std::cout << result << std::endl;
    }

    if (!response.getMessage().empty()) {
        std::cout << response.getMessage() << std::endl;
    }
}

