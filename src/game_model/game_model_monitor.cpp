#include <stdexcept>
#include <utility>
#include <numeric>
#include "game_model_monitor.h"

GameModelMonitor::GameModelMonitor() : model(), commands() {}

std::vector<std::string> GameModelMonitor::serializedRooms() {
    std::lock_guard<std::mutex> lock(mutex);

    return this->model.listRooms();
}

Response GameModelMonitor::listRooms() {
    std::vector<std::string> rooms = this->serializedRooms();
    std::string result;

    if (!rooms.empty()) {
        result = std::accumulate(
                std::next(rooms.begin()),
                rooms.end(),
                rooms.front(),
                [] (const std::string& a, const std::string& b)
                { return a + "\n" + b; });
    }

    return std::move(Response("OK", result.c_str()));
}

Response GameModelMonitor::createRoom(const char* name, uint8_t requiredPlayers) {
    std::lock_guard<std::mutex> lock(mutex);

    return std::move(Response("OK", this->model.createRoom(name, requiredPlayers).c_str()));
}

Response GameModelMonitor::joinRoom(const char* name) {
    std::lock_guard<std::mutex> lock(mutex);

    return std::move(Response("OK", this->model.joinRoom(name).c_str()));
}

Response GameModelMonitor::applyLogic(const Command& command) {
    if (command.getValue() == this->commands.DESERIALIZED_LIST)
        return std::move(this->listRooms());

    if (command.getValue() == this->commands.DESERIALIZED_CREATE)
        return std::move(this->createRoom(
                command.getSecondParameter().c_str(),
                std::stoi(command.getFirstParameter())));

    if (command.getValue() == this->commands.DESERIALIZED_JOIN)
        return std::move(this->joinRoom(command.getFirstParameter().c_str()));

    return {"ERROR", ""};
}
