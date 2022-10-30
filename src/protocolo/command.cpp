//
// Created by ignacio on 30/10/22.
//

#include "command.h"

Command::Command(char serialized, std::string &deserialized)
: serialized(serialized), deserialized(deserialized) {}

std::string Command::serialize() {
    //TODO serialize command
}