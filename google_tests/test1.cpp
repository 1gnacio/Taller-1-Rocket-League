#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"

void sendCommand(std::string& command) {
    Socket client("localhost", "8080");

    Command c = ProtocolCommands().createCommand(command);

    Protocolo().sendCommand(client, c);
}

TEST(Protocolo, ClienteEnviaIzquierdaPresionada) {
    Socket server("8080");

    std::string value = CommandValues().DESERIALIZED_LEFT_PUSHED;

    std::thread clientHandler(&sendCommand, std::ref(value));

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_LEFT_PUSHED);
}

TEST(Protocolo, ClienteEnviaNoOperation) {
    Socket server("8080");

    std::string value = CommandValues().DESERIALIZED_NOP;

    std::thread clientHandler(&sendCommand, std::ref(value));

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_NOP);
}