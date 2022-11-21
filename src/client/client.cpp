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
        isRunning(false), connection(connection) {}

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
    this->isRunning = true;
    sdl_handler.showWindow();

    std::thread standardInput(&Client::readStandardInput, this);
    std::thread drawThread(&Client::draw, this);
    std::thread updateThread(&Client::update, this);

    standardInput.join();
    drawThread.join();
    updateThread.join();
    sdl_handler.hideWindow();
}

void Client::addInputCommand(std::string deserialized_key) {
    ProtocolCommands makeCommands;
    std::cout << deserialized_key << std::endl;
    Command c = makeCommands.createCommand(this->connection.getId(), deserialized_key);
    this->connection.push(c);
}

void Client::update() {
    MatchResponse lastMatch(true);
    Response response = this->connection.pop();
    MatchResponse match = response.getMatchResponseByClientId(this->connection.getId());
    while (match.isDummy()) {
        response = this->connection.pop();
        match = response.getMatchResponseByClientId(this->connection.getId());
    }

    lastMatch = match;

    while (this->isRunning) {
        response = this->connection.pop();
        match = response.getMatchResponseByClientId(this->connection.getId());
        if (match.isDummy()) {
            sdl_handler.updateScreen(lastMatch);
        } else {
            sdl_handler.updateScreen(match);
        }
        lastMatch = match;
        this->screenUpdated = true;
    }
}

void Client::draw() {
    while (this->isRunning) {
        if (!this->screenUpdated) {
            continue;
        }
        Uint64 start = SDL_GetPerformanceCounter();

        sdl_handler.renderScreen();

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;

        if (16.666f - elapsedMS > 0) {
            SDL_Delay(floor(16.666f - elapsedMS));
        }
    }
}
