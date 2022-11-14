#include "sdl_player.h"

sdl_player::sdl_player(SDL2pp::Renderer &renderer): car(renderer, 4, DATA_PATH "/car/car"),
                                                    turbo(renderer, 10, DATA_PATH "/fire/fire"),
                                                    facingLeft(false), moving(false), onTurbo(false),
                                                    x(300), y(300), angle(0){
    car.setColorMod(255,255,255);
}


sdl_player::~sdl_player() {
    //TODO
}

void sdl_player::update(int _x, int _y, double _angle, float _dt) {
#ifndef SDL_TESTING
        this->x = _x;
        this->y = _y;
        this->angle = _angle;
#endif

    if (moving) {
        car.update(_dt);
#ifdef SDL_TESTING
            if (facingLeft)
                x -= 5;
            else
                x += 5;
#endif
    }
    if (onTurbo) {
        turbo.update(_dt);
    }

#ifdef SDL_TESTING
    if(onTurbo && moving){
            if (facingLeft)
                x -= 5;
            else
                x += 5;
    }
#endif
}

void sdl_player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    int size_h= 11 * renderer.GetOutputHeight() /100;
    int size_w= size_h*3;
    car.render(renderer, SDL2pp::Rect(x, y, size_w, size_h), angle,flip);

    if (onTurbo){
        if(facingLeft){
            turbo.render(renderer, SDL2pp::Rect(x+(size_h*3), y+(size_h/4), size_h, size_h), angle, flip);
        } else
            turbo.render(renderer, SDL2pp::Rect(x-(size_h), y+(size_h/4), size_h, size_h), angle, flip);
    }
}


#ifdef SDL_TESTING
void sdl_player::moveRight() {
    moving = true;
    facingLeft = false;
}

void sdl_player::moveLeft() {
    moving = true;
    facingLeft = true;
}

void sdl_player::stopMoving() {
    moving = false;
}

void sdl_player::toggleTurbo() {
    onTurbo = !onTurbo;
}
#endif