#ifndef ROCKET_LEAGUE_SDL_MAIN_H
#define ROCKET_LEAGUE_SDL_MAIN_H

#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"
#include <SDL_mixer.h>
#include <list>
#include <vector>
#include <map>
#include "sdl_animation.h"
#include "sdl_player.h"
#include "sdl_ball.h"
#include "sdl_scoreboard.h"
#include "sdl_arena.h"
#include "sdl_waiting.h"
#include "sdl_statistics.h"

#include <ctime>
#include "../src/common/unit_conversion.h"
#include "../src/configuration/attributes/client_configuration_attributes.h"
#ifndef SDL_TESTING
#include "../src/protocolo/responses/response.h"

#endif

#define TIME_UPDATE_MS 20

class sdl_main {
private:
    ClientConfigurationAttributes& conf;
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Mixer mixer;
    /*SDL2pp::Music background_music;*/
    sdl_arena arena;
    sdl_ball ball;
    sdl_scoreboard scoreboard;
    sdl_waiting waiting;
    sdl_statistics statistics;
    unit_conversion convert;
    int myID;
#ifndef SDL_TESTING
    std::map<int, sdl_player> players;
#endif

public:
    explicit sdl_main(ClientConfigurationAttributes& conf);
    void renderScreen();
    void showWindow();
    void hideWindow();
    void setID(int id);
    ~sdl_main() = default;

#ifndef SDL_TESTING
    void updateScreen(Response& response);
#else
    void updateScreen();
    sdl_player my_object;
#endif

};

#endif //ROCKET_LEAGUE_SDL_MAIN_H
