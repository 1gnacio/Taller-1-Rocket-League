#include "sdl_player.h"

sdl_player::sdl_player(SDL2pp::Renderer &renderer): car(renderer, 4, DATA_PATH "/car2/car"),
                                                    turbo(renderer, 10, DATA_PATH "/fire/fire"),
                                                    facingLeft(false), moving(false), onTurbo(false),
                                                    x(300), y(300), angle(0), dt(0) {
    car.setColorMod(255,255,255);
}


sdl_player::~sdl_player() {
    //TODO
}

void sdl_player::update(int _x, int _y, double _angle, float _dt) {
    //this->x = _x;
    this->y = _y;
    this->angle = _angle;
    this->dt = _dt; //TODO: se podría sacar

    if (moving) {
        car.update(dt);
        if (facingLeft)
            x -= 5;
        else
            x += 5;
    }
    if (onTurbo){
        turbo.update(dt);
    }
}

void sdl_player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    int size_h= 10 * renderer.GetOutputHeight() /100;
    int size_w= 12 * renderer.GetOutputWidth() /100;

    car.render(renderer, SDL2pp::Rect(x, y, size_h*3, size_h), angle,flip);

    if (onTurbo){
        if(facingLeft){
            turbo.render(renderer, SDL2pp::Rect(x+180, y+20, size_h*3, size_h), angle, flip);
        } else
            turbo.render(renderer, SDL2pp::Rect(x-180, y+20, size_h*3, size_h), angle, flip);
    }
}



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

void sdl_player::toogleTurbo() {
    onTurbo = !onTurbo;
}
