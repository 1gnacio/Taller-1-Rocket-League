#include "sdl_player.h"

sdl_player::sdl_player(SDL2pp::Renderer &renderer,
                       bool localTeam, bool mainPlayer):
        car_an(renderer, 4, DATA_PATH "/car/car"),
        turbo_an(renderer, 4, DATA_PATH "/car_turbo/car"),
        jump_an(renderer, 10, DATA_PATH "/jump/jump"),
        facingLeft(true), moving(false), onTurbo(false), jumping(false),
        x(0), y(0), angle(0), size_w(0), size_h(0){
    if (mainPlayer) {
        car_an.setColorMod(255,255,255);
    } else if (localTeam) {
        car_an.setColorMod(255,60,60);
    } else {
        car_an.setColorMod(60,60,255);
    }
}

void sdl_player::update(int _x, int _y, int _size_w, int _size_h,
                        double _angle, unsigned int dt, bool isMoving, bool isJumping,
                        bool _onTurbo, bool _facingLeft) {

        this->x = _x;
        this->y = _y;
        this->jumping = isJumping;
        this->onTurbo = _onTurbo;
        this->moving = isMoving;
        this->size_h = _size_h;
        this->size_w = _size_w;
        this->facingLeft = _facingLeft;
    this->angle = _angle;

    if (moving) {
        car_an.update(dt);
    }
    if (onTurbo) {
        turbo_an.update(dt);
    }

    if (jumping){
        jump_an.update(dt);
    }
}

void sdl_player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    int car_x=x-(size_w/2);
    int car_y=y-(size_h/2);
    int turbo_w = turbo_an.getWidth() * size_w / car_an.getWidth();
    int turbo_h = turbo_an.getHeight() * size_h / car_an.getHeight();

    if (onTurbo){
            turbo_an.render(renderer, SDL2pp::Rect(car_x, car_y,
                                                 turbo_w, turbo_h), angle, flip);
    } else {
        car_an.render(renderer, SDL2pp::Rect(car_x, car_y,
                                             size_w, size_h), angle, flip);
    }
//    if (onTurbo){
//        if (facingLeft){
//            turbo_r_an.render(renderer, SDL2pp::Rect(
//                    car_x+size_w, car_y,
//                    size_h*2, size_h*2), angle, turbo_flip);
//
//        } else {
//            turbo_r_an.render(renderer, SDL2pp::Rect(
//                    car_x-(size_w/2), car_y,
//                    size_h*2, size_h*2), angle, turbo_flip);
//        }
//    }
    if (jumping){
        jump_an.render(renderer, SDL2pp::Rect(
                car_x, car_y+(size_h/2), size_h*3,
                size_h*3), 0,  flip);
    }
}