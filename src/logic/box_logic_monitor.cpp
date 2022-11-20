#include "box_logic_monitor.h"

void BoxLogicMonitor::addPlayer(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    this->gamePhysics.addPlayer(id);
}

void BoxLogicMonitor::removePlayer(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    this->gamePhysics.removePlayer(id);
}