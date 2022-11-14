#ifndef __SDL_PLAYER_H__
#define __SDL_PLAYER_H__

#include <SDL2pp/SDL2pp.hh>
#include "sdl_animation.h"
class sdl_player {
private:
    sdl_animation animation;
    bool facingLeft;
    int x;
    int y;
    int angle;
public:
    explicit sdl_player(SDL2pp::Texture &texture);
    ~sdl_player();
    void update(int x, int y, int angle, float dt);
    void render(SDL2pp::Renderer &renderer);
};

#endif // __SDL_PLAYER_H__