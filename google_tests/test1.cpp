#include <thread>
#include "gtest/gtest.h"
#include "../src/sockets/socket.h"
#include "../src/constants/command_values.h"
#include "../src/protocolo/commands/command.h"
#include "../src/protocolo/protocol_commands.h"
#include "../src/protocolo/protocolo.h"

void sendCommand() {
    Socket client("localhost", "8080");

    std::string input = CommandValues().DESERIALIZED_LEFT_PUSHED;

    Command c = ProtocolCommands().createCommand(input);

    Protocolo().sendCommand(client, c);
}

TEST(Protocolo, ClienteEnviaIzquierdaPresionada) {
    Socket server("8080");

    std::thread clientHandler(&sendCommand);

    Socket connectedClient = server.accept();

    Command c = Protocolo().receiveCommand(connectedClient);

    clientHandler.join();

    EXPECT_EQ(c.getValue(), CommandValues().DESERIALIZED_LEFT_PUSHED);
}
