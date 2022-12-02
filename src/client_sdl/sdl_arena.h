
#ifndef ROCKET_LEAGUE_SDL_ARENA_H
#define ROCKET_LEAGUE_SDL_ARENA_H


#include "libs/libSDL2pp/SDL2pp/SDL2pp.hh"

class sdl_arena {
private:
    SDL2pp::Texture texture_stadium;
    SDL2pp::Texture texture_goal;
    int goal_w;
public:
    explicit sdl_arena(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(int goal_w);
    ~sdl_arena() = default;
};


#endif //ROCKET_LEAGUE_SDL_ARENA_H
