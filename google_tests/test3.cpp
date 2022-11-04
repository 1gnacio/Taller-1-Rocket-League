#include "gtest/gtest.h"
#include "../src/logicGame/game.h"

TEST(logicaDeJuego, cantidadDeComandosCorrectosLuegoDeAñadirlos){
    Game game;
    game.addCommand(Command(0x31, "CREAR", 123256,"Partida1", "6"));
    game.addCommand(Command(0x32, "UNIRSE", 12356,"Partida1"));

    EXPECT_EQ(2,game.numberOfCommand());
}
