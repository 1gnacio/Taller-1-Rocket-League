//
// Created by taller on 06/11/22.
//

#include "gameLogic.h"

GameLogic::GameLogic() {

}

void GameLogic::update(Command &command) {
    /*
     * Si el comando es unirse boxLogic.addPlayer();
     * Si el comando es moverse derecha .... boxLogic.moveRightStart(Xjugador)
     * Si el comando es parar de moverse a la derecha .... boxLogic.moveRightEnd(Xjugador)
     */
}

void GameLogic::update() { // Es necesario?
}

Response GameLogic::getResponse(){
    /* getStatusBall() - Devuelve datos sobre la pelota
     * getStatusGame() - Devuelve datos sobre el juego
     * getStatusCars() - Devuleve datos sobre los autos
     */
    std::vector<char> responseVec;
    return responseVec;

}
