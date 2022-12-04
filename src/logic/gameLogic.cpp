#include "gameLogic.h"
#include <iostream>
#include "../src/constants/command_values.h"
#include "../src/constants/logic_values.h"
#include <vector>
#include <utility>

GameLogic::GameLogic(): withoutPlayers(0) {
}



void GameLogic::updateModel(Command &command) {
    //std::cout << "llega un comando de " << command.getValue() <<", Con ID:" << command.getID() <<std::endl;
    if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().LEFT_DIRECTION);
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_RELEASE ||
               command.getValue() == CommandValues().DESERIALIZED_RIGHT_RELEASE) {
        gamePhysics.stopMove(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_RIGHT_PUSHED) {
        gamePhysics.startMove(command.getID(),
                              LogicValues().RIGHT_DIRECTION);
    } else if (command.getValue() == CommandValues().DESERIALIZED_TURBO_PUSHED) {
        gamePhysics.applyTurbo(command.getID());
    } else if (command.getValue() == CommandValues().DESERIALIZED_JUMP_PUSHED) {
        gamePhysics.jump(command.getID());
    } else if ((command.getValue() == CommandValues().DESERIALIZED_DOWN_PUSHED)) {
        gamePhysics.updateLastDirection(command.getID(), CommandValues().DESERIALIZED_DOWN_PUSHED);
    } else if((command.getValue() == CommandValues().DESERIALIZED_UP_PUSHED)) {
        gamePhysics.updateLastDirection(command.getID(), CommandValues().DESERIALIZED_UP_PUSHED);
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

bool GameLogic::matchFinished() {
    return (gamePhysics.matchFinished());
}

Response GameLogic::getResponse() {
    BallResponse ball(this->gamePhysics.getBallData(LogicValues().POS_X),
                 this->gamePhysics.getBallData(LogicValues().POS_Y),
                 this->gamePhysics.getBallData(LogicValues().ANGLE),
                 abs(this->gamePhysics.getBallData(LogicValues().Y_VELOCITY)) +
                 abs(this->gamePhysics.getBallData(LogicValues().X_VELOCITY)) > 0,
                 this->gamePhysics.getBallData(LogicValues().POS_Y) < 2.2f,
                 this->gamePhysics.getBallDataPunched(LogicValues().HAS_BEEN_PUNCHED_NORMAL),
                 this->gamePhysics.getBallDataPunched(LogicValues().HAS_BEEN_PUNCHED_FLIP_SHOT),
                 this->gamePhysics.getBallDataPunched(LogicValues().HAS_BEEN_PUNCHED_RED_SHOT),
                 this->gamePhysics.getBallDataPunched(LogicValues().HAS_BEEN_PUNCHED_PURPLE_SHOT),
                 this->gamePhysics.getBallDataPunched(LogicValues().HAS_BEEN_PUNCHED_GOLD_SHOT));

    PlayerResponses players = gamePhysics.getPlayersData();

    MatchResponse match(gamePhysics.gameData(ball, players));

    Response response(match);
    return std::move(response);
}

void GameLogic::resetData() {
    gamePhysics.resetData();

}

float GameLogic::ballPosY() {
    return gamePhysics.getBallData(LogicValues().POS_Y);
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

void GameLogic::updateRoomInfo(Room &room, bool replay) {
    gamePhysics.setRoomInfo(room, replay);
}
