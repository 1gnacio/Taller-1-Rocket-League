#include "sdl_ball.h"

sdl_ball::sdl_ball(SDL2pp::Renderer &renderer):
    texture_ball(renderer, DATA_PATH "/ball.png"),
    width(0), x(0), y(0), angle(0) {}

void sdl_ball::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture_ball, SDL2pp::NullOpt
                  , SDL2pp::Rect(x - (width/2), y-(width/2), width, width),
                  angle, SDL2pp::NullOpt, SDL_FLIP_NONE);
}

void sdl_ball::update(int _x, int _y, double _angle, int _width) {
    this->x = _x;
    this->y = _y;
    this->angle = _angle;
    this->width = _width;
}
