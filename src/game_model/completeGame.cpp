#include "completeGame.h"
#include "../src/constants/response_values.h"

CompleteGame::CompleteGame(int ownerId, int requiredPlayers, const char *name, ServerEndpoint& serverEndPoint):
        serverEndpoint(serverEndPoint),
        room(ownerId,requiredPlayers,name),
        logic(){
        this->logic.addPlayer(ownerId);
}



ActionResultResponse CompleteGame::joinPlayer(int id) {
    ActionResultResponse response = this->room.joinPlayer(id);
    if (response.getStatus() == ResponseValues().OK) {
        logic.addPlayer(id);
    }
    return response;
}

RoomResponse CompleteGame::list() {
    return room.list();
}

ActionResultResponse CompleteGame::leaveRoom(int playerId) {
    ActionResultResponse response = room.leaveRoom(playerId);
    if (response.getStatus() == ResponseValues().OK) {
        logic.removePlayer(playerId);
    }
    return response;
}

bool CompleteGame::playerInRoom(int id) {
    return room.playerInRoom(id);
}

void CompleteGame::applyCommand(Command &command) {
    if(command.getValue() != CommandValues().DESERIALIZED_NOP) {
        logic.updateModel(command);
    }
    logic.updateRoomInfo(this->room);
    logic.updateTime();
    sendResponse();
}
void CompleteGame::sendResponse() {
    this->serverEndpoint.push(logic.getResponse());
}


float CompleteGame::ballPosY() {

    return logic.ballPosY();
}

Response CompleteGame::getResponse() {
    RoomResponse roomResponse = this->room.list();
    LobbyResponse lobby;
    lobby.addRoom(roomResponse);
    Response response = logic.getResponse();
    response.addLobbyResponse(lobby);
    return response;
}

void CompleteGame::updateTime() {
    logic.updateTime();
}

void CompleteGame::resetData() {
    logic.resetData();

}

bool CompleteGame::isInGame() {
    return room.isInGame();
}
