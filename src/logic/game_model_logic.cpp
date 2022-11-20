#include <algorithm>
#include "game_model_logic.h"

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

void GameModelLogic::updateModel(Command &command) {
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
                  command.getValue()) != this->movementCommands.end()) {
        this->applyMatchLogic(command);
    }
}

void GameModelLogic::applyMatchLogic(Command &command) {
    if (command.getValue() == this->commands.DESERIALIZED_CREATE) {
        this->gamesLogic.emplace_back(std::make_unique<GameLogic>(command.getID(), command.getSecondParameter().c_str()));
    }

    auto match = std::find_if(this->gamesLogic.begin(),
                              this->gamesLogic.end(),
                              [&command] (GameLogic &logic)
                              { return logic.getName() == command.getFirstParameter(); });

    bool matchFound = match != this->gamesLogic.end();

    if (command.getValue() == this->commands.DESERIALIZED_JOIN &&
        matchFound) {
        (*match)->addPlayer(command.getID());
    }

    if ((command.getValue() == this->commands.DESERIALIZED_QUIT_MATCH ||
        command.getValue() == this->commands.DESERIALIZED_QUIT_GAME) &&
        matchFound) {
        (*match)->removePlayer(command.getID());
    }
}
