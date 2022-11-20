#include "box_logic_monitor.h"
#include "../src/constants/command_values.h"

void BoxLogicMonitor::addPlayer(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    this->gamePhysics.addPlayer(id);
}

void BoxLogicMonitor::removePlayer(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    this->gamePhysics.removePlayer(id);
}

bool BoxLogicMonitor::hasPlayer(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    return this->gamePhysics.hasPlayer(id);
}

BallResponse BoxLogicMonitor::getBallResponse() {
    std::lock_guard<std::mutex> lock(mutex);
    return this->gamePhysics.getBallResponse();
}

PlayerResponses BoxLogicMonitor::getPlayerResponses() {
    std::lock_guard<std::mutex> lock(mutex);
    return this->gamePhysics.getPlayersData();
}

float BoxLogicMonitor::getCarData(int carNumber, int key) {
    std::lock_guard<std::mutex> lock(mutex);
    return this->gamePhysics.getCarData(carNumber, key);
}

void BoxLogicMonitor::updateTime() {
    std::lock_guard<std::mutex> lock(mutex);
    this->gamePhysics.updateTime();
    this->gamePhysics.updateStatus();
}

float BoxLogicMonitor::playersAmount() {
    std::lock_guard<std::mutex> lock(mutex);
    return this->gamePhysics.playersAmount();
}

void BoxLogicMonitor::applyLogic(Command &command) {
    std::lock_guard<std::mutex> lock(mutex);

   if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().LEFT_DIRECTION);
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_RELEASE ||
               command.getValue() == CommandValues().DESERIALIZED_RIGHT_RELEASE) {
        gamePhysics.stopMove(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_RIGHT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().RIGHT_DIRECTION);

    } else if (command.getValue() == CommandValues().DESERIALIZED_TURBO_PUSHED) {
        gamePhysics.applyTurbo(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_JUMP_PUSHED) {
        gamePhysics.jump(command.getID());
    }
}
