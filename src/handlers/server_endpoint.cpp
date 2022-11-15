#include <algorithm>
#include "server_endpoint.h"

ServerEndpoint::ServerEndpoint() :
isActive(true),
receivedCommands(),
responses(),
connections(),
sender(std::thread(&ServerEndpoint::sendResponsesHandler, this)) {}

void ServerEndpoint::sendResponsesHandler() {
    while (this->isActive) {
        Response r = this->responses.pop();
        for (auto& connection : connections) {
            connection->push(r);
        }
    }
}

void ServerEndpoint::addPlayer(Socket &client) {
    this->connections.emplace_back(std::make_unique<ClientConnection>(client, this->responses, this->receivedCommands));
}

void ServerEndpoint::push(Response response) {
    this->responses.push(response);
}

Command ServerEndpoint::pop() {
    return this->receivedCommands.pop();
}

bool waitIfFinished(std::unique_ptr<ClientConnection>& connection) {
    return connection->connectionClosed();
}

void ServerEndpoint::stopConnections() {
    for(auto& connection : this->connections) {
        connection->closeConnection();
    }
}

void ServerEndpoint::cleanFinishedConnections() {
    this->connections.erase(std::remove_if(this->connections.begin(),
                                        this->connections.end(),
                                        waitIfFinished),
                         this->connections.end());
}

ServerEndpoint::~ServerEndpoint() {
    for(auto& connection : this->connections) {
        connection->closeConnection();
    }
    this->isActive = false;
    this->sender.join();
}

bool ServerEndpoint::queueEmpty() {
    return receivedCommands.isEmpty();
}
