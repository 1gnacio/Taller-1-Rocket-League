#include <algorithm>
#include "game_model.h"
#include "../constants/response_values.h"
#include "completeGame.h"
#include "src/constants/command_values.h"
#include "src/protocolo/protocol_commands.h"
#include <iostream>

RoomResponses GameModel::listRooms() {
    RoomResponses responses;

    for (auto& room : this->games) {
        RoomResponse r = room->list();
        responses.addRoom(r);
    }

    return responses;
}

ActionResultResponse GameModel::createRoom(int ownerId, const char* name, int requiredPlayers) {
    CommandValues values;
    std::vector<std::string> deserializedCommands({
                                                   values.DESERIALIZED_JOIN,
                                                  });
    Command command = ProtocolCommands().createCommand(ownerId, deserializedCommands[0]);
    if (findGame(name) == nullptr) {
        this->games.emplace_back(std::make_unique<CompleteGame>(ownerId, requiredPlayers, name));
        games[games.size()-1]->applyCommand(command);
        return {ownerId, ResponseValues().OK};
    }

    return {ownerId, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_EXISTS};
}

std::unique_ptr<CompleteGame>* GameModel::findGame(const char* name) {
    std::string roomName = name;
    for(auto &x: games) {
        if (x->getName() == roomName) {
            return &x;
        }
    }
    return nullptr;
}

std::unique_ptr<CompleteGame>* GameModel::findGame(int id) {

    for(auto &x: games) {
        if (x->playerInRoom(id)) {
            return &x;
        };
    }
    return nullptr;
}

ActionResultResponse GameModel::joinRoom(int playerId, const char* name) {

    if (findGame(name) != nullptr) {
        return (*findGame(name))->joinPlayer(playerId);
    }

    return {playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND};
}

ActionResultResponse GameModel::leaveRoom(int playerId, const char *name) {
    auto room = findGame(name);

    if (room != nullptr) {
        return (*room)->leaveRoom(playerId);
    }

    return {playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND};
}


void GameModel::applyCommandToGame(Command &command) {
    (*findGame(command.getID()))->applyCommand(command);
}

int GameModel::gamesAmount() {
    return games.size();
}

std::vector<Response> GameModel::getResponse() {
    std::vector<Response> responses;
    for(auto &x: games) {
        responses.emplace_back(x->getResponse());
    }
    return responses;
}

void GameModel::updateTime() {
    for(auto &x:games) {
        x->updateTime();
    }

}

void GameModel::resetDataOfGames() {
    for(auto &x:games) {
        x->resetData();
    }

}
