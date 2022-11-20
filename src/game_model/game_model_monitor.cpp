#include <utility>
#include "game_model_monitor.h"
#include "../src/constants/response_values.h"

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

LobbyResponse GameModelMonitor::applyLogic(const Command& command) {
    if (command.getValue() == this->commands.DESERIALIZED_CREATE)
        return std::move(this->createRoom(command.getID(),
                                          command.getSecondParameter().c_str(),
                                          std::stoi(command.getFirstParameter())));

    if (command.getValue() == this->commands.DESERIALIZED_JOIN)
        return std::move(this->joinRoom(command.getID(),
                                        command.getFirstParameter().c_str()));

    if (command.getValue() == this->commands.DESERIALIZED_QUIT_MATCH)
        return std::move(this->leaveRoom(command.getID(),
                                         command.getFirstParameter().c_str()));

    return std::move(this->listRooms(command.getID()));
}
