#include "sdl_player.h"

sdl_player::sdl_player(SDL2pp::Renderer &renderer):
    car_an(renderer, 4, DATA_PATH "/car/car"),
    turbo_an(renderer, 10, DATA_PATH "/fire/fire"),
    jump_an(renderer, 10, DATA_PATH "/jump/jump"),
    facingLeft(true), moving(false), onTurbo(false), jumping(false),
    x(0), y(0), angle(0), size_h(0), size_w(0){
    //car_an.setColorMod(255,255,255);
    jump_an.disableLoop();
}


sdl_player::~sdl_player() {
    //TODO
}

void sdl_player::update(int _x, int _y, int _size_w, int _size_h,
                        double _angle, float dt, bool isMoving, bool isJumping,
                        bool _onTurbo, bool _facingLeft) {
#ifndef SDL_TESTING
        this->x = _x;
        this->y = _y;
        this->jumping = isJumping;
        this->onTurbo = _onTurbo;
        this->moving = isMoving;
        this->size_h = _size_h;
        this->size_w = _size_w;
        this->facingLeft = _facingLeft;
#endif


    this->angle = _angle;

    if (moving) {
        car_an.update(dt);
#ifdef SDL_TESTING
            if (facingLeft)
                x -= 5;
            else
                x += 5;
#endif
    }
    if (onTurbo) {
        turbo_an.update(dt);
    }

    if (jumping){
        jump_an.update(dt);
#ifdef SDL_TESTING
        y-=5;
#endif
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
    car_an.render(renderer, SDL2pp::Rect(x-(size_w/2), y-(size_h/2),
                                         size_w, size_h), angle, flip);

    if (onTurbo){
        if (facingLeft){
            turbo_an.render(renderer, SDL2pp::Rect(
                    (x-(size_w/2)) + (size_h * 3),(y-(size_h/2)) + (size_h / 4),
                    size_h, size_h), angle, flip);
        } else {
            turbo_an.render(renderer, SDL2pp::Rect(
                    (x - (size_w / 2)) - (size_h),
                    (y - (size_h / 2)) + (size_h / 4),
                    size_h, size_h), angle, flip);
        }
    }
    if (jumping){
        jump_an.render(renderer, SDL2pp::Rect(
                x-(size_w/2), y-(size_h/2), size_h*3,
                size_h*3), 0,  flip);
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

void sdl_player::jump() {
    jumping=true;
}

void sdl_player::stopJump() {
    jumping=false;
    y=450;
}

#endif