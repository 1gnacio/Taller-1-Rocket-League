#include "gameLogic.h"
#include <iostream>
#include "../src/exceptions/blocking_queue_closed_exception.h"
#include <vector>
#include <utility>

GameLogic::GameLogic(int ownerId, const char *name) :
commandCount(0),
gamePhysics(),
game(name),
commandQueue(),
withoutPlayers(0),
updateModelHandler(std::thread(&GameLogic::updateModel, this)) {
    this->gamePhysics.addPlayer(ownerId);
}

void GameLogic::updateModel() {
    Command command = this->commandQueue.pop();

    std::cout << "llega un comando de " << command.getValue() << std::endl;
    /*if (this->withoutPlayers == 0) {
        this->gamePhysics.addPlayer(command.getID());
        withoutPlayers = 1;
    }*/
    if (command.getValue() == CommandValues().DESERIALIZED_TURBO_RELEASE) {
        this->gamePhysics.addPlayer(command.getID()); // this->gamePhysics.addPlayer(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().LEFT_DIRECTION);
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_RELEASE ||
               command.getValue() == CommandValues().DESERIALIZED_RIGHT_RELEASE) {
        gamePhysics.stopMove(command.getID());  // gamePhysics.stopMove(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_RIGHT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().RIGHT_DIRECTION);  // gamePhysics.startMove(command.getID(), LogicValues().RIGHT_DIRECTION);

    } else if (command.getValue() == CommandValues().DESERIALIZED_TURBO_PUSHED) {
        gamePhysics.applyTurbo(command.getID());  // gamePhysics.applyTurbo(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_JUMP_PUSHED) {
        gamePhysics.jump(command.getID());  // gamePhysics.jump(command.getID());
    }

    this->commandCount++;

    if (this->commandCount > 50) {
        gamePhysics.updateTime();
        gamePhysics.updateStatus();
        this->commandCount = 0;
    }
}

float GameLogic::getCarData(int carNumber, int key) {
    return gamePhysics.getCarData(carNumber, key);
}
float GameLogic::playersAmount() {
    return gamePhysics.playersAmount();
}

Response GameLogic::getResponse() {
    BallResponse ball(this->gamePhysics.getBallData(LogicValues().POS_X),
                 this->gamePhysics.getBallData(LogicValues().POS_Y),
                 this->gamePhysics.getBallData(LogicValues().ANGLE),
                 false, false, false);

    PlayerResponses players = gamePhysics.getPlayersData();

    std::vector<MatchResponse> matchs;
    matchs.emplace_back(MatchResponse(this->game.response(ball, players)));

    MatchResponses matches(matchs);

    Response response(matches);
    return std::move(response);
}

bool GameLogic::hasPlayer(int id) {
    return this->gamePhysics.hasPlayer(id);
}

GameLogic::~GameLogic() {
    this->updateModelHandler.join();
}
