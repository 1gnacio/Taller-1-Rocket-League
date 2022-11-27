#include "gameLogic.h"
#include <iostream>
#include "../src/constants/command_values.h"
#include "../src/constants/logic_values.h"
#include <vector>
#include <utility>

GameLogic::GameLogic(): withoutPlayers(0) {
}



void GameLogic::updateModel(Command &command) {
    std::cout << "llega un comando de " << command.getValue() <<", Con ID:" << command.getID() <<std::endl;
    if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED) {
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
}

float GameLogic::getCarData(int carNumber, int key) {
    return gamePhysics.getCarData(carNumber, key);
}
float GameLogic::playersAmount() {
    return gamePhysics.playersAmount();
}

void GameLogic::updateTime() {
    gamePhysics.updateTime();
    gamePhysics.updateStatus();
}

Response GameLogic::getResponse() {
    BallResponse ball(this->gamePhysics.getBallData(LogicValues().POS_X),
                 this->gamePhysics.getBallData(LogicValues().POS_Y),
                 this->gamePhysics.getBallData(LogicValues().ANGLE),
                 false, false, false);

    PlayerResponses players = gamePhysics.getPlayersData();

    MatchResponse match(gamePhysics.gameData(ball, players));

    Response response(match);
    return std::move(response);
}

void GameLogic::resetData() {
    gamePhysics.resetData();

}

float GameLogic::ballPosY() {
    gamePhysics.getBallData(LogicValues().POS_Y);
}

void GameLogic::addPlayer(int id) {
    gamePhysics.addPlayer(id);
}

void GameLogic::removePlayer(int id) {
    gamePhysics.removePlayer(id);
}

bool GameLogic::isGoal() {
    return this->gamePhysics.isGoal();
}
