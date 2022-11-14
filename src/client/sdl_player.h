#ifndef __SDL_PLAYER_H__
#define __SDL_PLAYER_H__

#include <SDL2pp/SDL2pp.hh>
#include "sdl_animation.h"

class sdl_player {
private:
    sdl_animation car;
    sdl_animation turbo;
    bool facingLeft;
    bool moving;
    bool onTurbo;
    int x;
    int y;
    double angle;
    float dt;
public:
    explicit sdl_player(SDL2pp::Renderer &renderer);
    void update(int x, int y, double angle, float dt);
    void render(SDL2pp::Renderer &renderer);
    ~sdl_player();


    //TODO: sacar, es para pruebas.
    void moveRight();
    void moveLeft();
    void stopMoving();
    void toogleTurbo();

};

#endif // __SDL_PLAYER_H__