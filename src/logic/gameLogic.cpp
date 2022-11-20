#include "gameLogic.h"
#include <iostream>

GameLogic::GameLogic(int ownerId, const char *name) :
isStarted(true),
commandCount(0),
gamePhysics(),
game(name),
commandQueue(),
withoutPlayers(0),
updateModelHandler(std::thread(&GameLogic::updateModel, this)) {
    this->gamePhysics.addPlayer(ownerId);
}

void GameLogic::updateTime() {
    gamePhysics.updateTime();
}

void GameLogic::updateModel() {
    this->commandCount = 0;
    while (this->isStarted) {
        commandCount = 0;
        while(!commandQueue.empty() && commandCount < 50) {
            Command command = this->commandQueue.pop();
            std::cout << "llega un comando de " << command.getValue() << std::endl;
            this->gamePhysics.applyLogic(command);
            commandCount++;
        }
        //this->gamePhysics.updateTime();

    }
}

float GameLogic::getCarData(int carNumber, int key) {
    return gamePhysics.getCarData(carNumber, key);
}
float GameLogic::playersAmount() {
    return gamePhysics.playersAmount();
}

MatchResponse GameLogic::getResponse() {
    BallResponse ball = this->gamePhysics.getBallResponse();

    PlayerResponses players = this->gamePhysics.getPlayerResponses();

    return this->game.response(ball, players);
}

bool GameLogic::hasPlayer(int id) {
    return this->gamePhysics.hasPlayer(id);
}

GameLogic::~GameLogic() {
    this->isStarted = false;
    this->updateModelHandler.join();
}
