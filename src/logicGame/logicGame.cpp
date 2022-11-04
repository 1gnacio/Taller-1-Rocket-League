#include "logicGame.h"
#include <iostream>

LogicGame::LogicGame() {

}

void LogicGame::clearQueue(std::queue<std::byte> &queue){
    while(!queue.empty()){
        queue.pop();
    }
}

void LogicGame::update(std::queue<std::byte> &queue) {
   this->clearQueue(queue);

}
