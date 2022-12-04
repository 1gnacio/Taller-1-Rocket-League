//
// Created by igb on 03/12/22.
//

#include "sdl_waiting.h"
sdl_waiting::sdl_waiting(SDL2pp::Renderer &renderer):
    waiting_an(renderer, 8, DATA_PATH "/waiting/waiting"),
    active(false) {}

void sdl_waiting::render(SDL2pp::Renderer &renderer) {
    if (active) {
        int size_w=50;
        int size_h=50;
        waiting_an.render(renderer,
                          SDL2pp::Rect((renderer.GetOutputWidth()/2)-(size_w/2),
                               (renderer.GetOutputHeight()/2)-(size_h/2),
                               size_w, size_h),
                          0, SDL_FLIP_NONE);
    }
}

void sdl_waiting::update(bool _active) {
    this->active = _active;
    waiting_an.update(FRAME_RATE);
}

