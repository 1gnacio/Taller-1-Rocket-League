#include "sdl_ball.h"

sdl_ball::sdl_ball(SDL2pp::Renderer &renderer):
    texture_ball(renderer, DATA_PATH "/ball.png"),
    width(0), x(0), y(0), shot(NORMAL) {}

void sdl_ball::render(SDL2pp::Renderer &renderer) {
    switch (shot) {
        case NORMAL:
            texture_ball.SetColorMod(255,255,255);
            break;
        case FLIP:
            texture_ball.SetColorMod(100,255,100);
            break;
        case RED:
            texture_ball.SetColorMod(255,69,0);
            break;
        case PURPLE:
            texture_ball.SetColorMod(128,0,128);
            break;
        case GOLD:
            texture_ball.SetColorMod(255,215,0);
            break;
        default:
            texture_ball.SetColorMod(255,255,255);
            break;
    }
    renderer.Copy(texture_ball, SDL2pp::NullOpt
                  , SDL2pp::Rect(x - (width/2), y-(width/2), width, width),
                  angle, SDL2pp::NullOpt, SDL_FLIP_NONE);
}

void sdl_ball::update(int _x, int _y, double _angle, int _width,
                      bool redShot, bool goldShot, bool flipShot, bool purpleShot) {
    this->x = _x;
    this->y = _y;
    this->angle = _angle;
    this->width = _width;

    if (redShot)
        shot = RED;
    else if (goldShot)
        shot = GOLD;
    else if (flipShot)
        shot=FLIP;
    else if (purpleShot)
        shot= PURPLE;
    else
        shot = NORMAL;
}
