#include <algorithm>
#include "game_model_logic.h"
#include <iostream>

GameModelLogic::GameModelLogic() :
gamesLogic(),
commands(),
actionCommands({
    this->commands.DESERIALIZED_JOIN,
    this->commands.DESERIALIZED_CREATE,
    this->commands.DESERIALIZED_QUIT_MATCH,
    this->commands.DESERIALIZED_QUIT_GAME}),
    movementCommands({
        this->commands.DESERIALIZED_UP_PUSHED,
        this->commands.DESERIALIZED_UP_RELEASE,
        this->commands.DESERIALIZED_DOWN_PUSHED,
        this->commands.DESERIALIZED_DOWN_RELEASE,
        this->commands.DESERIALIZED_LEFT_PUSHED,
        this->commands.DESERIALIZED_LEFT_RELEASE,
        this->commands.DESERIALIZED_RIGHT_PUSHED,
        this->commands.DESERIALIZED_RIGHT_RELEASE,
        this->commands.DESERIALIZED_JUMP_PUSHED,
        this->commands.DESERIALIZED_JUMP_RELEASE,
        this->commands.DESERIALIZED_TURBO_PUSHED,
        this->commands.DESERIALIZED_TURBO_RELEASE,
    }){}
/*
 * Busca la partida a partir de los ID.
 * Si la encuentra, pushea a la cola de comandos de la partida el comando recibido.
 */
void GameModelLogic::updateModel(Command &command, bool lobbyStatusOk) {
    if (std::find(this->movementCommands.begin(),
                  this->movementCommands.end(),
                  command.getValue()) != this->movementCommands.end()) {
        auto match = std::find_if(this->gamesLogic.begin(),
                  this->gamesLogic.end(),
                  [&command] (std::unique_ptr<GameLogic> &logic)
                  { return logic->hasPlayer(command.getID()); });

        if (match == this->gamesLogic.end()) {
            return;
        }
        (*match)->push(command);
    }

    if (std::find(this->actionCommands.begin(),
                  this->actionCommands.end(),
                  command.getValue()) != this->movementCommands.end()
                  && lobbyStatusOk) {
        this->applyMatchAction(command);
    }
}

void GameModelLogic::applyMatchAction(Command &command) {
    if (command.getValue() == this->commands.DESERIALIZED_CREATE) {
        this->gamesLogic.emplace_back(std::make_unique<GameLogic>(command.getID(), command.getSecondParameter().c_str()));
    }

    if (command.getValue() == this->commands.DESERIALIZED_JOIN) {
        auto match = std::find_if(this->gamesLogic.begin(),
                                  this->gamesLogic.end(),
                                  [&command] (std::unique_ptr<GameLogic> &logic)
                                  { return logic->getName() == command.getFirstParameter(); });
        if (match != this->gamesLogic.end()) {
            (*match)->addPlayer(command.getID());
        }
    }

    if ((command.getValue() == this->commands.DESERIALIZED_QUIT_MATCH ||
        command.getValue() == this->commands.DESERIALIZED_QUIT_GAME)) {
        auto match = std::find_if(this->gamesLogic.begin(),
                                  this->gamesLogic.end(),
                                  [&command] (std::unique_ptr<GameLogic> &logic)
                                  { return logic->hasPlayer(command.getID()); });
        (*match)->removePlayer(command.getID());
    }
}

MatchResponses GameModelLogic::getResponses() {
    MatchResponses responses;
    for (auto &logic : this->gamesLogic) {
        MatchResponse response = logic->getResponse();
        responses.addResponse(response);
    }

    return std::move(responses);
}

void GameModelLogic::updateTime() {
    for (auto &logic : this->gamesLogic) {
        logic->updateTime();
    }

}
