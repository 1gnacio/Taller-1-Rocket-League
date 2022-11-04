#include "gtest/gtest.h"
#include "../src/logicGame/logicGameMock.h"

TEST(logicaDeJuego, iniciarElJuegoRetornaCeroSiNoHuboFallos){
    LogicGameMock mock;

    EXPECT_EQ(0,mock.startGame());
}