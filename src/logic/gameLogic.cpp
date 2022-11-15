//
// Created by taller on 06/11/22.
//

#include "gameLogic.h"
#include <iostream>
#include "../src/constants/command_values.h"
#include "../src/constants/logic_values.h"
GameLogic::GameLogic(): withoutPlayers(0){

}

void GameLogic::updateModel(Command &command) {

    std::cout << "llega un comando de " << command.getValue() << std::endl;
    if(this->withoutPlayers == 0){
        this->gamePhysics.addPlayer();
        withoutPlayers = 1;
    }
    /*
    if (command.getValue() == CommandValues().DESERIALIZED_JOIN) {
        this->gamePhysics.addPlayer();
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED){
        gamePhysics.startMove(1, LogicValues().LEFT_DIRECTION);
    } else if (command.getValue() == CommandValues().DESERIALIZED_LEFT_PUSHED ||
               command.getValue() == CommandValues().DESERIALIZED_RIGHT_PUSHED) {
        gamePhysics.stopMove(1);
    } else if (command.getValue() == CommandValues().DESERIALIZED_RIGHT_PUSHED) {
        gamePhysics.startMove(1,LogicValues().RIGHT_DIRECTION);

    }
    */
}
void GameLogic::updateTime() {
    gamePhysics.updateTime();
}

Response GameLogic::getResponse(){

    //Se debe cambiar, se utiliza para no romper la conexión
    BallResponse ball(0, 0, 0, false, false, false);
    PlayerResponse  player(0, 0, 0, 0, false, false, false, false, false, false);
    std::vector<PlayerResponse> players{player};
    PlayerResponses playerResponses(players);
    std::string name = "nombre";
    MatchResponse matchResponse(0, 0, 0, ball, playerResponses, 0, 0, name, false, false, false, false, false);
    std::vector<MatchResponse> responses{matchResponse};
    MatchResponses matchResponses(responses);
    Response response(matchResponses);
    return response;

}
