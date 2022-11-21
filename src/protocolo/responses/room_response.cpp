#include "room_response.h"
#include "../serializer/serializer.h"

std::vector<unsigned char> RoomResponse::serialize() {
    std::vector<unsigned char> serialization;
    std::vector<unsigned char> result;
    Serializer serializer;

    serializer.merge(serialization, this->clients.serialize());
    serializer.merge(serialization, serializer.serializeString(this->name));
    serializer.merge(serialization, serializer.serializeInt(this->requiredPlayers));
    serializer.merge(serialization, serializer.serializeInt(this->currentPlayers));
    serializer.merge(serialization, serializer.serializeBool(this->waitingPlayers));
    serializer.merge(serialization, serializer.serializeBool(this->isStarted));
    serializer.merge(serialization, serializer.serializeBool(this->isFinished));

    serializer.merge(result, serializer.serializeInt(serialization.size()));
    serializer.merge(result, serialization);

    return result;
}

RoomResponse::RoomResponse(std::vector<unsigned char> &serialized) {
    Serializer serializer;
    int begin = 0;
    int end = 0;
    int playerCount = 0;
    serializer.parse(playerCount, serialized, begin, end);
    this->clients = ConnectedClients(std::vector<unsigned char>(serialized.begin(),
                                                                serialized.begin() +
                                                                ConnectedClients::size(playerCount) +
                                                                sizeof(playerCount)));

    begin += ConnectedClients::size(playerCount);
    end += ConnectedClients::size(playerCount);

    serializer.parse(this->name, serialized, begin, end);
    serializer.parse(this->requiredPlayers, serialized, begin, end);
    serializer.parse(this->currentPlayers, serialized, begin, end);
    serializer.parse(this->waitingPlayers, serialized, begin, end);
    serializer.parse(this->isStarted, serialized, begin, end);
    serializer.parse(this->isFinished, serialized, begin, end);
}

RoomResponse::RoomResponse(std::string &name, int requiredPlayers, int currentPlayers,
                           bool waitingPlayers, bool isStarted, bool isFinished) :
                           clients(), name(name), requiredPlayers(requiredPlayers), currentPlayers(currentPlayers),
                           waitingPlayers(waitingPlayers), isStarted(isStarted), isFinished(isFinished) {}

void RoomResponse::addClient(int id) {
    this->clients.addClient(id);
}

bool RoomResponse::getWaitingForPlayers() {
    return this->waitingPlayers;
}

const std::string &RoomResponse::getName() {
    return this->name;
}

int RoomResponse::getCurrentPlayers() {
    return this->currentPlayers;
}

int RoomResponse::getRequiredPlayers() {
    return this->requiredPlayers;
}
