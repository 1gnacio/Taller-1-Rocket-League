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
socket(hostname, servname),
cQueue(),
rQueue(),
senderHandler(socket, cQueue, SENDER),
receiverHandler(socket, rQueue, RECEIVER) {}

void Client::readStandardInput() {
    // SDL leer entrada estandar

    // una vez capturada la entrada y creado el comando correspondiente, hacer push a la cola
    ProtocolCommands makeCommands;
    Command c = makeCommands.createCommand((std::string &) "LEFT");
    cQueue.push(c);
}

void Client::run() {
    std::thread standardInput(&Client::readStandardInput, this);
    while (this->isRunning) {
        Response r = this->rQueue.pop();
        // dibujar
    }
}

