#include <iostream>
#include <string>
#include "client.h"

// hilos:

//       uno que dibuja (hilo principal), pop respuestas
//       otro que lee de entrada estandar y arma los comandos, push comandos
//       otro que envia los comandos, pop comandos
//       y otro que recibe las respuestas, push respuestas

//       hay una cola de comandos y otra de respuestas, ambas compartidas
Client::Client(const char *hostname, const char *servname) :
isRunning(true),
connection(hostname, servname) {}

void Client::readStandardInput() {
    // SDL leer entrada estandar

    // una vez capturada la entrada y creado el comando correspondiente, hacer push a la cola
    ProtocolCommands makeCommands;
    std::string example = CommandValues().DESERIALIZED_NOP;
    Command c = makeCommands.createCommand(example);
    this->connection.push(c);
}

void Client::run() {
    std::thread standardInput(&Client::readStandardInput, this);
    while (this->isRunning) {
        Response r = this->connection.pop();
        // dibujar
    }
}

