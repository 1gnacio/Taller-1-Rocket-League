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
    return lobbyR;
}

void GameModel::gameFlow(std::unique_ptr<CompleteGame>* completeGame) {
    (*completeGame)->gameFlow();
}

std::thread GameModel::initGame(std::unique_ptr<CompleteGame>* completeGame) {

    std::thread t(&GameModel::gameFlow, this, completeGame );
    return t;
}

LobbyResponse GameModel::createRoom(int ownerId, const char* name, int requiredPlayers) {
    auto found = std::find_if(this->games.begin(),
                              this->games.end(),
                              [&name](const std::unique_ptr<CompleteGame>& game)
                              {return game->getName() == name;});

    if (found == this->games.end()) {
        this->games.emplace_back(std::make_unique<CompleteGame>(ownerId, requiredPlayers, name, serverEndpoint));
        this->gamesThread.push_back(initGame(&games.back()));

        // games[games.size()-1]->applyCommand(command);
        ActionResultResponse actionResultAux(ownerId, ResponseValues().OK);
        LobbyResponse lobbyR(actionResultAux);
        return lobbyR;
    }
    ActionResultResponse actionResultAux(ownerId, ResponseValues().ERROR, ResponseValues().ROOM_ALREADY_EXISTS);
    LobbyResponse lobbyR(actionResultAux);
    return lobbyR;
}

LobbyResponse GameModel::joinRoom(int playerId, const char* name) {
    auto found = std::find_if(this->games.begin(),
                              this->games.end(),
                              [&name](const std::unique_ptr<CompleteGame>& game)
                              {return game->getName() == name;});

    if (found != this->games.end()) {
        ActionResultResponse actionResult((*found)->joinPlayer(playerId));
        LobbyResponse lobbyR(actionResult);
        return lobbyR;
    }
    ActionResultResponse actionResultAux(playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyR(actionResultAux);
    return lobbyR;
}

LobbyResponse GameModel::leaveRoom(int playerId, const char *name) {
    auto found = std::find_if(this->games.begin(),
                              this->games.end(),
                              [&name] (const std::unique_ptr<CompleteGame>& game)
                              { return game->getName() == name;});

    if (found != this->games.end()) {
        ActionResultResponse actionResult((*found)->leaveRoom(playerId));
        if (!(*found)->hasPlayers() && (*found)->matchFinished()) {
            this->games.erase(std::remove(this->games.begin(),
                                          this->games.end(),
                                          *found), this->games.end());
        }
        LobbyResponse lobbyR(actionResult);
        return lobbyR;
    }
    ActionResultResponse actionResultAux(playerId, ResponseValues().ERROR, ResponseValues().ROOM_NOT_FOUND);
    LobbyResponse lobbyR(actionResultAux);
    return lobbyR;
}

void GameModel::applyCommandToGame(Command &command) {
    auto found = std::find_if(this->games.begin(),
                              this->games.end(),
                              [&command](const std::unique_ptr<CompleteGame>& game)
                              {return game->playerInRoom(command.getID());});

    if(found != this->games.end() && (*found)->isInGame()) {
        (*found)->applyCommand(command);
        (*found)->resetData();
    }
}

int GameModel::gamesAmount() {
    return games.size();
}

std::vector<Response> GameModel::getResponse() {
    std::vector<Response> responses;
    std::transform(this->games.begin(),
                   this->games.end(),
                   std::back_inserter(responses),
                   [](std::unique_ptr<CompleteGame> &game)
                   {return game->getResponse();});

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

GameModel::GameModel(ServerEndpoint &serverEndpoint): serverEndpoint(serverEndpoint) {}

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

    if((command.getValue() != commands.DESERIALIZED_NOP)) {
        this->applyCommand(command);
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

void GameModel::applyCommand(Command& command) {
    auto found = std::find_if(this->games.begin(),
                 this->games.end(),
                 [&command] (std::unique_ptr<CompleteGame>& game)
                 { return game->playerInRoom(command.getID());});

    if (found != this->games.end()) {
        (*found)->applyCommand(command);
    }
}

bool GameModel::gameExists(const char *name) {
    auto found = std::find_if(this->games.begin(),
                              this->games.end(),
                              [&name] (const std::unique_ptr<CompleteGame>& game)
                              { return game->getName() == name;});

    return found != this->games.end();
}
