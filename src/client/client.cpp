#include <string>
#include "client.h"
#include <SDL2pp/SDL2pp.hh>
// hilos:

//       uno que dibuja (hilo principal), pop respuestas
//       otro que lee de entrada estandar y arma los comandos, push comandos
//       otro que envía los comandos, pop comandos
//       y otro que recibe las respuestas, push respuestas

//       hay una cola de comandos y otra de respuestas, ambas compartidas

Client::Client(ServerConnection& connection) :
        isRunning(true), connection(connection), sdl_handler() {
}

void Client::readStandardInput() {
    //TODO: opción para que el usurario pueda elegir las teclas.
    SDL_Event event;
    while (this->isRunning){
        //Ver que convine después. ¿waitEvent y pollEvent?
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        addInputCommand(CommandValues().
                            DESERIALIZED_LEFT_PUSHED);
                        break;
                    case SDLK_RIGHT:
                        addInputCommand(CommandValues().
                            DESERIALIZED_RIGHT_PUSHED);
                        break;
                    case SDLK_UP:
                        addInputCommand(CommandValues().
                            DESERIALIZED_UP_PUSHED);
                        break;
                    case SDLK_DOWN:
                        addInputCommand(CommandValues().
                            DESERIALIZED_DOWN_PUSHED);
                        break;
                    case SDLK_SPACE:
                        addInputCommand(CommandValues().
                            DESERIALIZED_JUMP_PUSHED);
                        break;
                    case SDLK_t:
                        addInputCommand(CommandValues().
                            DESERIALIZED_TURBO_PUSHED);
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        addInputCommand(CommandValues().
                            DESERIALIZED_LEFT_RELEASE);
                        break;
                    case SDLK_RIGHT:
                        addInputCommand(CommandValues().
                            DESERIALIZED_RIGHT_RELEASE);
                        break;
                    case SDLK_UP:
                        addInputCommand(CommandValues().
                            DESERIALIZED_UP_RELEASE);
                        break;
                    case SDLK_DOWN:
                        addInputCommand(CommandValues().
                            DESERIALIZED_DOWN_RELEASE);
                        break;
                    case SDLK_SPACE:
                        addInputCommand(CommandValues().
                            DESERIALIZED_JUMP_RELEASE);
                        break;
                    case SDLK_t:
                        addInputCommand(CommandValues().
                            DESERIALIZED_TURBO_RELEASE);
                        break;
                }
            }// Fin KEY_UP
                break;
            case SDL_QUIT:
                this->isRunning = false;
                quitMatch();
                break;
        }
    }

}

void Client::run() {
    this->isRunning = true;
    sdl_handler.showWindow();
    std::thread standardInput(&Client::readStandardInput, this);

    while (this->isRunning) {
        Response response = this->connection.pop();
        sdl_handler.updateScreen(response);
        sdl_handler.renderScreen();
        SDL_Delay(TIME_UPDATE_MS);
    }
    standardInput.join();
    sdl_handler.hideWindow();
    this->connection.clearGameName();
}

void Client::addInputCommand(std::string deserialized_key) {
    ProtocolCommands makeCommands;
    Command c = makeCommands.createCommand(
            this->connection.getId(), deserialized_key);
    this->connection.push(c);
}

void Client::quitMatch() {
    ProtocolCommands makeCommands;
    std::string value = CommandValues().DESERIALIZED_QUIT_MATCH;
    std::string gameName = this->connection.getGameName();
    Command c = makeCommands.createCommand(this->connection.getId(),
                                           value,
                                           gameName);
    this->connection.push(c);
}
