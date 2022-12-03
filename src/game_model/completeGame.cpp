#include <csignal>
#include "completeGame.h"
#include "../src/constants/response_values.h"
#include <iostream>

CompleteGame::CompleteGame(int ownerId, int requiredPlayers, const char *name, ServerEndpoint& serverEndPoint):
        serverEndpoint(serverEndPoint),
        room(ownerId,requiredPlayers,name),
        logic()
        , replayLogic(5 /*configurable*/, 25 /*respuestas enviadas por el servidor por segundo*/),
        isClosed(false){
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
    commandQueue.push(command);
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

void CompleteGame::finally() {
    this->isClosed = true;
}

bool CompleteGame::matchFinished() {
    return (logic.matchFinished());
}

void CompleteGame::gameFlow() {

    try {
        while(!this->isClosed && !this->matchFinished()) {
            logic.updateRoomInfo(this->room, this->replayLogic.isInReplay());
            logic.resetData();
            if(isInGame()) {
                int limitCommands = 0;
                while(!commandQueue.isEmpty() && limitCommands <= 50 || (this->replayLogic.isInReplay())){
                    logic.updateRoomInfo(this->room, this->replayLogic.isInReplay());
                    logic.resetData();
                    if (this->replayLogic.isInReplay()) {
                        Response replayResponse = this->replayLogic.getResponse();
                        if (!replayResponse.dummy()) {
                            this->serverEndpoint.push(replayResponse);
                        } else {
                            this->serverEndpoint.push(logic.getResponse());
                        }
                        float timeStep = 1.0f / 25.0f;
                        usleep(timeStep*1000000);
                    } else {
                        Command command = commandQueue.pop();
                        if(command.getValue() != CommandValues().DESERIALIZED_NOP) { // NO DEBERIA LLEGAR EL COMANDO NOP
                            logic.updateModel(command);
                        }
                        limitCommands++;
                    }
                }
                if (!this->replayLogic.isInReplay()) {
                    logic.updateTime();
                    if (logic.isGoal()) {
                        this->replayLogic.goalScored();
                    }
                    Response response = logic.getResponse();
                    this->replayLogic.addResponse(response);
                    sendResponse();
                }
            } else {
                sendResponse();
                float timeStep = 1.0f / 10.0f;
                usleep(timeStep*1000000);

            }
        }
    } catch (...) {
        throw;
    }
}

bool CompleteGame::isInReplay() {
    return (this->replayLogic.isInReplay());
}

