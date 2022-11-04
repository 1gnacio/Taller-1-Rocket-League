#include "gtest/gtest.h"
#include "../src/logicGame/game.h"

TEST(logicaDeJuego, sinComandosEnColaLuegoDeActualizar){
    Game game;
    game.addCommand(std::byte(0));
    game.addCommand(std::byte(1));
    game.addCommand(std::byte(3));

    game.updateModel();

    EXPECT_EQ(0,game.numberOfCommand());
}
