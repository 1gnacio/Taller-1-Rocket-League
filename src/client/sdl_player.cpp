#include "sdl_player.h"

sdl_player::sdl_player(SDL2pp::Texture &texture): animation(texture), x(300), y(300) {}

sdl_player::~sdl_player() {}

void sdl_player::update(int x, int y, int angle, float dt) {
    animation.update(dt);
}

void sdl_player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    animation.render(renderer, SDL2pp::Rect(x, y, 200, 200), flip);
}