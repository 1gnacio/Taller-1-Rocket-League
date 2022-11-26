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
            std::lock_guard<std::mutex> l(mutex);
            for (auto& connection : connections) {
                if (r.isRecipient(connection->getId())){
                    connection->push(r);
                }
            }
        }
    } catch (std::exception &e) {
        this->isActive = false;
    }
}

void ServerEndpoint::addPlayer(Socket &client) {
    std::lock_guard<std::mutex> l(mutex);
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
    return connection->connectionClosed();
}

void ServerEndpoint::stopConnections() {
    std::lock_guard<std::mutex> l(mutex);
    for(auto& connection : this->connections) {
        connection->closeConnection();
    }
}

void ServerEndpoint::cleanFinishedConnections() {
    std::lock_guard<std::mutex> l(mutex);
    this->connections.erase(std::remove_if(this->connections.begin(),
                                        this->connections.end(),
                                        waitIfFinished),
                         this->connections.end());
}

ServerEndpoint::~ServerEndpoint() {
    this->responses.close();
    std::lock_guard<std::mutex> l(mutex);
    for(auto& connection : this->connections) {
        connection->closeConnection();
    }
    this->isActive = false;
    this->sender.join();
}

bool ServerEndpoint::queueEmpty() {
    return receivedCommands.isEmpty();
}
