#include <algorithm>
#include "game_model.h"
#include "../constants/response_values.h"
#include "completeGame.h"
#include <iostream>

LobbyResponse GameModel::listRooms(int clientId) {
    RoomResponses responses;

    for (auto& room : this->games) {
        RoomResponse r = room->list();
        responses.addRoom(r);
    }
    ActionResultResponse actionResult(clientId, ResponseValues().OK);
    LobbyResponse lobbyR(responses, actionResult);
    return std::move(lobbyR);
}

void GameModel::gameFlow(std::unique_ptr<CompleteGame>* completeGame) {
    (*completeGame)->gameFlow();
}

std::thread GameModel::initGame(std::unique_ptr<CompleteGame>* completeGame) {

    std::thread t(&GameModel::gameFlow, this, completeGame );
    return t;
}

LobbyResponse GameModel::createRoom(int ownerId, const char* name, int requiredPlayers) {
    if (findGame(name) == nullptr) {
        this->games.emplace_back(std::make_unique<CompleteGame>(ownerId, requiredPlayers, name, serverEndpoint));
        this->gamesThread.push_back(initGame(&games.back()));

        // games[games.size()-1]->applyCommand(command);
        ActionResultResponse actionResultAux(ownerId, ResponseValues().OK);
        LobbyResponse lobbyR(actionResultAux);
        return std::move(lobbyR);
    }
    ActionResultResponse actionResultAux(ownerId, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_EXISTS);
    LobbyResponse lobbyR(actionResultAux);
    return std::move(lobbyR);
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

LobbyResponse GameModel::joinRoom(int playerId, const char* name) {


    if (findGame(name) != nullptr) {

        ActionResultResponse actionResult((*findGame(name))->joinPlayer(playerId));
        LobbyResponse lobbyR(actionResult);
        return std::move(lobbyR);

    }

    ActionResultResponse actionResultAux(playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyR(actionResultAux);
    return std::move(lobbyR);
}

LobbyResponse GameModel::leaveRoom(int playerId, const char *name) {
    auto room = findGame(name);

    if (room != nullptr) {
        ActionResultResponse actionResult((*room)->leaveRoom(playerId));
        LobbyResponse lobbyR(actionResult);
        return std::move(lobbyR);
    }
    ActionResultResponse actionResultAux(playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyR(actionResultAux);
    return std::move(lobbyR);
}


void GameModel::applyCommandToGame(Command &command) {
    if(command.getValue() == CommandValues().DESERIALIZED_NOP) {
        for (auto &x : games) {
            if(x->isInGame()) {
            x->applyCommand(command);
            resetDataOfGames();
            }
        }
        return;
    }

    auto room = findGame(command.getID());
    if(room != nullptr) {
        if((*findGame(command.getID()))->isInGame()) {
            (*findGame(command.getID()))->applyCommand(command);
            resetDataOfGames();
        }
    }
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

GameModel::GameModel(ServerEndpoint &serverEndpoint): serverEndpoint(serverEndpoint) {

}

void GameModel::applyLogic(Command& command) {
    if (command.getValue() == this->commands.DESERIALIZED_LIST){
        LobbyResponse lobby(this->listRooms(command.getID()));
        Response responseAux(lobby);
        serverEndpoint.push(responseAux);
        return;
    }
    if (command.getValue() == this->commands.DESERIALIZED_CREATE) {
        LobbyResponse lobby(this->createRoom(command.getID(),
                         command.getSecondParameter().c_str(),
                         std::stoi(command.getFirstParameter())));
        Response responseAux(lobby);
        serverEndpoint.push(responseAux);
        return;
    }
    if (command.getValue() == this->commands.DESERIALIZED_JOIN) {
        LobbyResponse lobby(this->joinRoom(command.getID(),
                                           command.getFirstParameter().c_str()));
        Response responseAux(lobby);
        serverEndpoint.push(responseAux);
        return;
    }

    if (command.getValue() == this->commands.DESERIALIZED_QUIT_MATCH) {
        LobbyResponse lobby = this->leaveRoom(command.getID(),
                                         command.getFirstParameter().c_str());
        Response responseAux(lobby);
        serverEndpoint.push(responseAux);
        return;
    }

    if (command.getValue() == this->commands.DESERIALIZED_QUIT_GAME) {
        this->serverEndpoint.cleanFinishedConnections();
        return;
    }

    if((command.getValue() != commands.DESERIALIZED_NOP)) {
        if((*findGame(command.getID())) != nullptr) {
            if(!((*findGame(command.getID()))->isInReplay())) {
                (*findGame(command.getID()))->applyCommand(command);
            }
        }
    }
    // si no es ninguno -> cola de cada partida .
    // applyCommandToGame(command);
}

GameModel::~GameModel(){
    for(auto &x: games) {
        x->finally();
    }
    for(auto &x: gamesThread) {
        x.join();
    }
}
