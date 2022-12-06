
#ifndef ROCKET_LEAGUE_SDL_ARENA_H
#define ROCKET_LEAGUE_SDL_ARENA_H


#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"
#include "sdl_animation.h"
#include <string>

#define GOAL_WIDTH 0.7

class sdl_arena {
private:
    SDL2pp::Texture texture_stadium;
    SDL2pp::Texture texture_goal;
    SDL2pp::Font font;
    int goal_w;
    bool waitingForPlayer;
    bool replay;
    sdl_animation turboBar_an;
    int myID;
    void renderText(SDL2pp::Renderer &renderer,
                    const std::string& text, int x, int y, bool background);
public:
    explicit sdl_arena(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(int goal_w, bool waitingForPlayer,
                bool replay, float turboLeft, int myID);
    ~sdl_arena() = default;
};


#endif //ROCKET_LEAGUE_SDL_ARENA_H
