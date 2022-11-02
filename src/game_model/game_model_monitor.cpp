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

    return std::move(Response(
            result.c_str(),
            "OK"));
}

Response GameModelMonitor::createRoom(const char* name, uint8_t requiredPlayers) {
    std::lock_guard<std::mutex> lock(mutex);

    return std::move(Response(this->model.createRoom(name, requiredPlayers).c_str()));
}

Response GameModelMonitor::joinRoom(const char* name) {
    std::lock_guard<std::mutex> lock(mutex);

    return std::move(Response(this->model.joinRoom(name).c_str()));
}

Response GameModelMonitor::applyLogic(const Command& command) {
    if (command.getValue() == this->commands.listValue) {
        return std::move(this->listRooms());
    } else if (command.getValue() == this->commands.createValue) {
        return std::move(this->createRoom(
                command.getSecondArgument().c_str(),
                std::stoi(command.getFirstArgument())));
    } else if (command.getValue() == this->commands.joinValue) {
        return std::move(this->joinRoom(
                command.getFirstArgument().c_str()));
    } else {
        return Response("ERROR");
    }
}
