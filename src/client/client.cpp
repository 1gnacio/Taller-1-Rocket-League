#include <iostream>
#include <string>
#include "client.h"
#include <SDL2pp/SDL2pp.hh>
#include <unistd.h>
// hilos:

//       uno que dibuja (hilo principal), pop respuestas
//       otro que lee de entrada estandar y arma los comandos, push comandos
//       otro que envía los comandos, pop comandos
//       y otro que recibe las respuestas, push respuestas

//       hay una cola de comandos y otra de respuestas, ambas compartidas

Client::Client(ServerConnection& connection) :
        isRunning(true), connection(connection)/*, my_lobby()*/{
    addInputCommand(CommandValues().DESERIALIZED_TURBO_RELEASE);
}

void Client::readStandardInput() {
    //TODO: opción para que el usurario pueda elegir las teclas.
    SDL_Event event;
    bool quit = false;
    while (!quit){
        //Ver que convine después. ¿waitEvent y pollEvent?
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_KEYDOWN: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        addInputCommand(CommandValues().DESERIALIZED_LEFT_PUSHED);
                        break;
                    case SDLK_RIGHT:
                        addInputCommand(CommandValues().DESERIALIZED_RIGHT_PUSHED);
                        break;
                    case SDLK_UP:
                        addInputCommand(CommandValues().DESERIALIZED_UP_PUSHED);
                        break;
                    case SDLK_DOWN:
                        addInputCommand(CommandValues().DESERIALIZED_DOWN_PUSHED);
                        break;
                    case SDLK_SPACE:
                        addInputCommand(CommandValues().DESERIALIZED_JUMP_PUSHED);
                        break;
                    case SDLK_t:
                        addInputCommand(CommandValues().DESERIALIZED_TURBO_PUSHED);
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        addInputCommand(CommandValues().DESERIALIZED_LEFT_RELEASE);
                        break;
                    case SDLK_RIGHT:
                        addInputCommand(CommandValues().DESERIALIZED_RIGHT_RELEASE);
                        break;
                    case SDLK_UP:
                        addInputCommand(CommandValues().DESERIALIZED_UP_RELEASE);
                        break;
                    case SDLK_DOWN:
                        addInputCommand(CommandValues().DESERIALIZED_DOWN_RELEASE);
                        break;
                    case SDLK_SPACE:
                        addInputCommand(CommandValues().DESERIALIZED_JUMP_RELEASE);
                        break;
                    case SDLK_t:
                        addInputCommand(CommandValues().DESERIALIZED_TURBO_RELEASE);
                        break;
                }
            }// Fin KEY_UP
                break;
            case SDL_QUIT:
                std::cout << "Quit" << std::endl;
                quit = true;
                addInputCommand(CommandValues().DESERIALIZED_QUIT_MATCH);
                this->isRunning = false;
                break;
        }
        //SDL_Delay(UPDATE_TIME);   //TODO: ver
    }

}

void Client::run() {
    sdl_handler.showWindow();
    std::thread standardInput(&Client::readStandardInput, this);

    while (this->isRunning) {
        Response response = this->connection.pop();
        sdl_handler.updateScreen(response);
        sdl_handler.renderScreen();
        SDL_Delay(5);   //TODO: ver
    }

    standardInput.join();
    sdl_handler.hideWindow();
}

void Client::addInputCommand(std::string deserialized_key) {
    ProtocolCommands makeCommands;
    std::cout << deserialized_key << std::endl;
    Command c = makeCommands.createCommand(this->connection.getId(), deserialized_key);
    this->connection.push(c);
}