//
// Created by igb on 03/12/22.
//

#ifndef ROCKET_LEAGUE_SDL_WAITING_H
#define ROCKET_LEAGUE_SDL_WAITING_H


#include <SDL2pp/SDL2pp.hh>
#include "sdl_animation.h"

class sdl_waiting {
private:
    sdl_animation waiting_an;
    bool active;
public:
    explicit sdl_waiting(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(bool active);
    ~sdl_waiting() = default;
};


#endif //ROCKET_LEAGUE_SDL_WAITING_H
