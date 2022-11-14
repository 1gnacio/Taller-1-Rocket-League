//
// Created by igb on 14/11/22.
//
#include <SDL2pp/SDL2pp.hh>
#include <iostream>
#include <exception>
#include <unistd.h>

#include "src/client/sdl_player.h"

static bool handleEvents(sdl_player &player);
static void render(SDL2pp::Renderer &renderer, sdl_player &player);
static void update(sdl_player &player, float dt);

int main(int argc, char** argv){
    try {
        // Inicializo biblioteca de SDL
        SDL2pp::SDL sdl(SDL_INIT_VIDEO);
        // Creo una ventana dinamica con título "Hello world"
        SDL2pp::Window window("Hello world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              800, 600, SDL_WINDOW_RESIZABLE);

        // Creo renderer
        SDL2pp::Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        sdl_player py(renderer);

        bool running = true;
        // Gameloop, notar como tenemos desacoplado el procesamiento de los inputs (handleEvents)
        // del update del modelo.
        while (running) {
            running = handleEvents(py);
            update(py, FRAME_RATE);
            render(renderer, py);

            // la cantidad de segundos que debo dormir se debe ajustar en función
            // de la cantidad de tiempo que demoró el handleEvents y el render
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
    while(SDL_PollEvent(&event)){
        switch(event.type) {
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
//                    case SDLK_SPACE:
//                        player.toggleTurbo();
//                        break;
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

static void render(SDL2pp::Renderer &renderer, sdl_player &player) {
    renderer.Clear();
    player.render(renderer);
    renderer.Present();
}

static void update(sdl_player &player, float dt) {
    player.update(100, 400, 0, dt);
}