//
// Created by ignacio on 04/11/22.
//

#ifndef RECEIVE_COMMANDS_HANDLER_H
#define RECEIVE_COMMANDS_HANDLER_H

#include <vector>
#include "command_handler.h"

class ReceiveCommandsHandler {
private:
    std::vector<std::unique_ptr<CommandHandler>> handlers;
public:
};


#endif // RECEIVE_COMMANDS_HANDLER_H
