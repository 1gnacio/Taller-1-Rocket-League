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

void GameLogic::updateModel() {
    while (this->isStarted) {
        Command command = this->commandQueue.pop();

        //std::cout << "llega un comando de " << command.getValue() << std::endl;
        /*if (this->withoutPlayers == 0) {
            this->gamePhysics.addPlayer(command.getID());
            withoutPlayers = 1;
        }*/
        this->gamePhysics.applyLogic(command);

        this->commandCount++;

        if (this->commandCount > 50) {
            this->gamePhysics.updateTime();
            this->commandCount = 0;
        }
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
