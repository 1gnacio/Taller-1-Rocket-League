//
// Created by taller on 04/11/22.
//

#include "game.h"

Game::Game() {

}
int Game::startGame() {

}
void Game::updateModel() {
    logic.update(inputQueue);
}
void Game::addCommand(Command command) {
    inputQueue.push(std::move(command));
}
void Game::removeLastCommand() {
    inputQueue.pop();
}

int Game::numberOfCommand(){
    return inputQueue.size();
}
