#include "logicGame.h"
#include <iostream>

LogicGame::LogicGame() {

}

void LogicGame::clearQueue(std::queue<Command> &queue){
    while(!queue.empty()){
        queue.pop();
    }
}

void LogicGame::update(std::queue<Command> &queue) {
   this->clearQueue(queue);

}
