#ifndef __SDL_PLAYER_H__
#define __SDL_PLAYER_H__

#include <SDL2pp/SDL2pp.hh>
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
    float x;
    float y;
    double angle;
public:
    explicit sdl_player(SDL2pp::Renderer &renderer);
    void update(float x, float y, float angle, float dt);
    void render(SDL2pp::Renderer &renderer);
    ~sdl_player();

#ifdef SDL_TESTING
    void moveRight();
    void moveLeft();
    void stopMoving();
    void toggleTurbo();
    void jump();
    void stopJump();
#endif
};

#endif // __SDL_PLAYER_H__