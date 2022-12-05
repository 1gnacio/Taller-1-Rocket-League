//
// Created by igb on 14/11/22.
//
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "src/client_sdl/sdl_player.h"
#include "src/client_sdl/sdl_main.h"
#include "src/configuration/yaml_configuration.h"
#include "../src/configuration/attributes/client_configuration_attributes.h"

static bool handleEvents(sdl_player &player);

int main(int argc, char** argv){
    try {
        ClientConfigurationAttributes config = YamlConfiguration().ReadClientConfiguration();
        sdl_main py(config);
        bool running = true;
        while (running) {
            running = handleEvents(py.my_object);
            py.updateScreen();
            py.renderScreen();
            usleep(FRAME_RATE);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

/**
 * Va a tomar un evento de teclado, y actualizará el modelo en función de los eventos que lleguen.
 * En un juego real no se tomará de a un evento por vuelta del gameloop, sino que se deberán tomar TODOS
 * o N eventos por vuelta
 */
static bool handleEvents(sdl_player &player) {
    SDL_Event event;
    // Para el alumno: Buscar diferencia entre waitEvent y pollEvent
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_KEYDOWN: {
                // ¿Qué pasa si mantengo presionada la tecla?
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.moveLeft();
                        break;
                    case SDLK_RIGHT:
                        player.moveRight();
                        break;
                    case SDLK_SPACE:
                        player.toggleTurbo();
                        break;
                    case SDLK_UP:
                        player.jump();
                        break;
                }
            } // Fin KEY_DOWN
                break;
            case SDL_KEYUP: {
                SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                switch (keyEvent.keysym.sym) {
                    case SDLK_LEFT:
                        player.stopMoving();
                        break;
                    case SDLK_RIGHT:
                        player.stopMoving();
                        break;
                    case SDLK_SPACE:
//                        player.toggleTurbo();
                        break;
                    case SDLK_UP:
                        player.stopJump();
                        break;
                }
            }// Fin KEY_UP
                break;
            case SDL_QUIT:
                std::cout << "Quit :(" << std::endl;
                return false;
        } // fin switch(event)
    } // fin while(SDL_PollEvents)
    return true;
}
