//
// Created by igb on 04/12/22.
//

#ifndef ROCKET_LEAGUE_SDL_STATISTICS_H
#define ROCKET_LEAGUE_SDL_STATISTICS_H

#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"
#include <string>
#include <vector>
#include "../src/protocolo/responses/player_response.h"

class sdl_statistics {
private:
    SDL2pp::Font font;
    SDL2pp::Texture background;
    std::vector<std::string> text;
    bool activate;
public:
    explicit sdl_statistics(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(std::vector<PlayerResponse> players);
    ~sdl_statistics() = default;
};


#endif //ROCKET_LEAGUE_SDL_STATISTICS_H
