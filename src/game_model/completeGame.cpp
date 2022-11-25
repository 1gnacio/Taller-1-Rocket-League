//
// Created by taller on 25/11/22.
//

#include "completeGame.h"
#include <iostream>

CompleteGame::CompleteGame(int ownerId, int requiredPlayers, const char *name, ServerEndpoint& serverEndPoint):
        serverEndpoint(serverEndPoint),
        room(ownerId,requiredPlayers,name),
        logic(){
        this->logic.addPlayer(ownerId);
}



ActionResultResponse CompleteGame::joinPlayer(int id) {
    CommandValues values;
    std::vector<std::string> deserializedCommands({
                                                          values.DESERIALIZED_JOIN,
                                                  });
    Command command = ProtocolCommands().createCommand(id, deserializedCommands[0]); // Refactorizar
    logic.updateModel(command);
    return room.joinPlayer(id);
}

RoomResponse CompleteGame::list() {
    return room.list();
}

ActionResultResponse CompleteGame::leaveRoom(int playerId) {
    return room.leaveRoom(playerId);
}

bool CompleteGame::playerInRoom(int id) {
    return room.playerInRoom(id);
}

void CompleteGame::applyCommand(Command &command, bool status) {
    if(status) {
        logic.updateModel(command);
    }
    logic.updateTime();
    this->serverEndpoint.push(logic.getResponse());
}

float CompleteGame::ballPosY() {

    return logic.ballPosY();
}

Response CompleteGame::getResponse() {
    return logic.getResponse();
}

void CompleteGame::updateTime() {
    logic.updateTime();
}

void CompleteGame::resetData() {
    logic.resetData();

}

