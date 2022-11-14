#ifndef ROCKET_LEAGUE_SDL_MAIN_H
#define ROCKET_LEAGUE_SDL_MAIN_H

#define UPDATE_TIME 200

#include <chrono>
#include <SDL2pp/SDL2pp.hh>
#include <list>
#include "../src/protocolo/responses/response.h"
#include "sdl_animation.h"
#include "sdl_player.h"
#include "sdl_ball.h"
#include "sdl_scoreboard.h"
#include "sdl_arena.h"
#include <ctime>


class sdl_main {
private:
    SDL2pp::SDL sdl;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    sdl_arena arena;
    sdl_ball ball;
    sdl_scoreboard scoreboard;
    std::list<sdl_player> players;
    long time;
    //TODO: sacar es para probar.
    int angle_test;
    int x_test;
    int y_test;
    float dt_test;
public:
    sdl_main();
    void updateScreen(const Response& response);
    void renderScreen();
    ~sdl_main();

};

#endif //ROCKET_LEAGUE_SDL_MAIN_H
