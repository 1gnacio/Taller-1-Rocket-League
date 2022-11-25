#include "gameLogic.h"
#include <iostream>
#include "../src/constants/command_values.h"
#include "../src/constants/logic_values.h"
#include <vector>
#include <utility>

GameLogic::GameLogic(): withoutPlayers(0) {
}

void GameLogic::updateModel(Command &command) {
    std::cout << "llega un comando de " << command.getValue() << std::endl;
    /*if (this->withoutPlayers == 0) {
        this->gamePhysics.addPlayer(command.getID());
        withoutPlayers = 1;
    }*/
    if (command.getValue() == CommandValues().DESERIALIZED_JOIN) {
        std::cout << "creo el auto" <<std::endl;
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

    std::vector<MatchResponse> matchs;
    matchs.emplace_back(MatchResponse(gamePhysics.gameData(ball, players)));

    MatchResponses matches(matchs);

    Response response(matches);
    return std::move(response);
}

void GameLogic::resetData() {
    gamePhysics.resetData();

}

float GameLogic::ballPosY() {
    gamePhysics.getBallData(LogicValues().POS_Y);
}
