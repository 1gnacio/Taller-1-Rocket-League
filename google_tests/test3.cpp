#include "gtest/gtest.h"
#include "../src/logicGame/game.h"

TEST(logicaDeJuego, cantidadDeComandosCorrectosLuegoDeAñadirlos){
    Game game;
    game.addCommand(std::byte(0));
    game.addCommand(std::byte(1));
    game.addCommand(std::byte(3));

    EXPECT_EQ(3,game.numberOfCommand());
}
