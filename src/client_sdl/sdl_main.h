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
#include "../src/protocolo/responses/response.h"
#include "sdl_music.h"


class sdl_main {
private:
    ClientConfigurationAttributes& conf;
    SDL2pp::SDL sdl;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SDL2pp::SDLTTF ttf;
    SDL2pp::Mixer mixer;
    sdl_arena arena;
    sdl_ball ball;
    sdl_scoreboard scoreboard;
    sdl_waiting waiting;
    sdl_statistics statistics;
    sdl_music sounds;
    unit_conversion convert;
    int myID;
    std::map<int, sdl_player> players;
    bool showStatistics;

public:
    explicit sdl_main(ClientConfigurationAttributes& conf);
    void renderScreen();
    void showWindow();
    void hideWindow();
    void setID(int id);
    void enableSounds();
    void disableSounds();
    ~sdl_main() = default;
    void updateScreen(Response& response);
};

#endif //ROCKET_LEAGUE_SDL_MAIN_H
