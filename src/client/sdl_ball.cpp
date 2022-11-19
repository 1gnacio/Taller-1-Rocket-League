
#include "sdl_ball.h"


sdl_ball::sdl_ball(SDL2pp::Renderer &renderer): texture_ball(renderer, DATA_PATH "/ball.png"),
            x(0), y(0), angle(0), radius(20) {}

void sdl_ball::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture_ball, SDL2pp::NullOpt, SDL2pp::Rect(x, y, radius*2, radius*2), angle, SDL2pp::NullOpt, SDL_FLIP_NONE);
}

void sdl_ball::update(int _x, int _y, double _angle, int _radius) {
    this->x = _x;
    this->y = _y;
    this->angle = _angle;
    this->radius = _radius;
}

