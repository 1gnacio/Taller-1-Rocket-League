#ifndef ROCKET_LEAGUE_SDL_MAIN_H
#define ROCKET_LEAGUE_SDL_MAIN_H

#include <SDL2pp/SDL2pp.hh>
#include <list>
#include <vector>
#include "sdl_animation.h"
#include "sdl_player.h"
#include "sdl_ball.h"
#include "sdl_scoreboard.h"
#include "sdl_arena.h"
#include <ctime>
#include "unit_conversion.h"

#ifndef SDL_TESTING
#include "../src/protocolo/responses/response.h"
#endif

class sdl_main {
private:
    SDL2pp::SDL sdl;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    sdl_arena arena;
    sdl_ball ball;
    sdl_scoreboard scoreboard;
    unit_conversion convert;
#ifndef SDL_TESTING
    std::list<sdl_player> players;
#endif
public:
    sdl_main();
    void renderScreen();
    void showWindow();
    void hideWindow();
    ~sdl_main();

#ifndef SDL_TESTING
    void updateScreen(Response& response);
#else
    void updateScreen();
    sdl_player my_object;
#endif

};

#endif //ROCKET_LEAGUE_SDL_MAIN_H
