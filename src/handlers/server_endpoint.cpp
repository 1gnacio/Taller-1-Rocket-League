#include <algorithm>
#include "server_endpoint.h"

ServerEndpoint::ServerEndpoint() :
isActive(true),
receivedCommands(),
responses(),
connections(),
sender(std::thread(&ServerEndpoint::sendResponsesHandler, this)) {}

void ServerEndpoint::sendResponsesHandler() {
    try {
        while (this->isActive) {
            Response r = this->responses.pop();
            for (auto& connection : connections) {
                if (connection &&
                    !connection->connectionClosed() &&
                    r.isRecipient(connection->getId())){
                    connection->push(r);
                }
            }
        }
    } catch (std::exception &e) {
        this->isActive = false;
    }
}

void ServerEndpoint::addPlayer(Socket &client) {
    this->connections.emplace_back(std::make_unique<ClientConnection>(this->nextClientId, this->receivedCommands, client));
    this->nextClientId++;
}

void ServerEndpoint::push(Response response) {
    this->responses.push(response);
}

Command ServerEndpoint::pop() {
    return this->receivedCommands.pop();
}

bool waitIfFinished(std::unique_ptr<ClientConnection>& connection) {
    return !connection || connection->connectionClosed();
}

void ServerEndpoint::stopConnections() {
    if (this->isActive) {
        this->responses.close();
        this->receivedCommands.close();
        for(auto& connection : this->connections) {
            connection->closeConnection();
        }
        this->isActive = false;
        this->sender.join();
    }
}

void ServerEndpoint::cleanFinishedConnections() {
    this->connections.erase(std::remove_if(this->connections.begin(),
                                        this->connections.end(),
                                        waitIfFinished),
                         this->connections.end());
}

ServerEndpoint::~ServerEndpoint() {
    if (this->isActive) {
        this->responses.close();
        this->receivedCommands.close();
        for(auto& connection : this->connections) {
            connection->closeConnection();
        }
        this->isActive = false;
        this->sender.join();
    }
}

bool ServerEndpoint::queueEmpty() {
    return receivedCommands.isEmpty();
}
