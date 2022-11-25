#include <stdexcept>
#include <utility>
#include <numeric>
#include "game_model_monitor.h"
#include "../src/constants/response_values.h"
#include "iostream"

GameModelMonitor::GameModelMonitor() : model(), commands() {}

LobbyResponse GameModelMonitor::listRooms(int id) {
    std::lock_guard<std::mutex> lock(mutex);

    RoomResponses rooms = this->model.listRooms();
    ActionResultResponse actionResponse(id, ResponseValues().OK);

    return std::move(LobbyResponse(rooms, actionResponse));
}

LobbyResponse GameModelMonitor::createRoom(int id, const char* name, int requiredPlayers) {
    std::lock_guard<std::mutex> lock(mutex);
    ActionResultResponse actionResponse = this->model.createRoom(id, name, requiredPlayers);
    RoomResponses rooms = this->model.listRooms();

    return std::move(LobbyResponse(rooms, actionResponse));
}

LobbyResponse GameModelMonitor::joinRoom(int id, const char* name) {
    std::lock_guard<std::mutex> lock(mutex);

    ActionResultResponse actionResponse = this->model.joinRoom(id, name);
    RoomResponses rooms = this->model.listRooms();

    return std::move(LobbyResponse(rooms, actionResponse));
}

LobbyResponse GameModelMonitor::leaveRoom(int id, const char *name) {
    std::lock_guard<std::mutex> lock(mutex);

    ActionResultResponse actionResponse = this->model.leaveRoom(id, name);
    RoomResponses rooms = this->model.listRooms();

    return std::move(LobbyResponse(rooms, actionResponse));
}

void GameModelMonitor::applyCommandToGame(Command& command) {
    std::lock_guard<std::mutex> lock(mutex);
    model.applyCommandToGame(command);
}

LobbyResponse GameModelMonitor::applyLogic(Command& command) {
    if (command.getValue() == this->commands.DESERIALIZED_LIST)
        return std::move(this->listRooms(command.getID()));

    if (command.getValue() == this->commands.DESERIALIZED_CREATE)
        return std::move(this->createRoom(command.getID(),
                                          command.getSecondParameter().c_str(),
                                          std::stoi(command.getFirstParameter())));

    if (command.getValue() == this->commands.DESERIALIZED_JOIN) // Modificar
        return std::move(this->createRoom(command.getID(),
                                          command.getSecondParameter().c_str(),
                                          2));
        /*return std::move(this->joinRoom(command.getID(),
                                        command.getFirstParameter().c_str()));*/

    if (command.getValue() == this->commands.DESERIALIZED_QUIT_MATCH)
        return std::move(this->leaveRoom(command.getID(),
                                         command.getFirstParameter().c_str()));

    applyCommandToGame(command);

    return {};
}

void GameModelMonitor::run() {
    /*
     * Mientras el server no cerro
     *  - Leo comandos y actualizo las salas
     */
}

int GameModelMonitor::gamesAmount() {
    std::lock_guard<std::mutex> lock(mutex);
    return model.gamesAmount();
}

std::vector<Response> GameModelMonitor::getResponse() {
     std::vector<Response> responses;
     responses = model.getResponse();
    return responses;
}

void GameModelMonitor::updateTime() {
    std::lock_guard<std::mutex> lock(mutex);
    model.updateTime();

}

void GameModelMonitor::resetDataOfGames() {
    model.resetDataOfGames();

}
