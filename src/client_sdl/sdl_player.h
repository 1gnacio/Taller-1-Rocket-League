#ifndef __SDL_PLAYER_H__
#define __SDL_PLAYER_H__

#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"
#include "sdl_animation.h"

class sdl_player {
private:
    sdl_animation car_an;
    sdl_animation turbo_an;
    sdl_animation jump_an;
    bool facingLeft;
    bool moving;
    bool onTurbo;
    bool jumping;
    int x;
    int y;
    double angle;
    int size_w;
    int size_h;

public:
    sdl_player(SDL2pp::Renderer &renderer,
               bool localTeam, bool mainPlayer);

    void update(int x, int y, int size_w, int size_h, double angle,
                bool isMoving, bool isJumping, bool onTurbo,
                bool facingLeft);

    void render(SDL2pp::Renderer &renderer);

    ~sdl_player() = default;
};
#endif // __SDL_PLAYER_H__
