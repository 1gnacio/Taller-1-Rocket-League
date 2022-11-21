#include "gameLogic.h"
#include <iostream>

GameLogic::GameLogic(int ownerId, const char *name) :
isStarted(true),
commandCount(0),
gamePhysics(),
game(name),
withoutPlayers(0) {
    this->gamePhysics.addPlayer(ownerId);
}

void GameLogic::updateTime() {
    gamePhysics.updateTime();
}

void GameLogic::updateModel(Command &command) {
    std::cout << "llega un comando de " << command.getValue() << std::endl;
    this->gamePhysics.applyLogic(command);
    commandCount++;
}

float GameLogic::getCarData(int carNumber, int key) {
    return gamePhysics.getCarData(carNumber, key);
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
}
