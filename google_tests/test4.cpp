#include "gtest/gtest.h"
#include "../src/logicGame/game.h"

TEST(logicaDeJuego, sinComandosEnColaLuegoDeActualizar){
    Game game;
    Command(0x32,"UNIRSE","partida1");

    game.updateModel();

    EXPECT_EQ(0,game.numberOfCommand());
}
