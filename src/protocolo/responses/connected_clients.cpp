#include "connected_clients.h"
#include "../serializer/serializer.h"

ConnectedClients::ConnectedClients(std::vector<unsigned char> serialized) : clients() {
    Serializer serializer;
    int begin = 0;
    int end = 0;
    int count = 0;

    serializer.parse(count, serialized, begin, end);

    for (int i = 0; i < count; i++) {
        int client = 0;
        serializer.parse(client, serialized, begin, end);
        this->clients.push_back(client);
    }
}

std::vector<unsigned char> ConnectedClients::serialize() {
    Serializer serializer;
    std::vector<unsigned char> result;

    int count = this->clients.size();

    serializer.merge(result, serializer.serializeInt(count));

    for (auto& client : this->clients) {
        serializer.merge(result, serializer.serializeInt(client));
    }

    return result;
}

ConnectedClients::ConnectedClients() {}

void ConnectedClients::addClient(int id) {
    this->clients.push_back(id);
}
