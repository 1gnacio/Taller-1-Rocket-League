//
// Created by igb on 03/12/22.
//

#include "sdl_waiting.h"
sdl_waiting::sdl_waiting(SDL2pp::Renderer &renderer):
    font(DATA_PATH "/Vera.ttf", 70),
    waiting_an(renderer, 8, DATA_PATH "/waiting/waiting"),
    active(false), currPlayers(0), totalPlayers(0) {}

void sdl_waiting::render(SDL2pp::Renderer &renderer) {
    if (active) {
        int size= renderer.GetOutputHeight()/6;
        std::string text = "Waiting for Players: " + std::to_string(totalPlayers);
        SDL2pp::Texture texture_text(renderer,
                                     font.RenderText_Blended(text,
                                     SDL_Color{255, 255, 255, 255}));
        int text_width=renderer.GetOutputWidth()/2;
        int text_height=renderer.GetOutputHeight()/10;
        int x = renderer.GetOutputWidth()/2;
        int y = renderer.GetOutputHeight()/4;
        renderer.Copy(texture_text, SDL2pp::NullOpt,
                      SDL2pp::Rect(x-(text_width/2), y-(text_height/2),
                                   text_width, text_height));
        waiting_an.render(renderer,
                          SDL2pp::Rect((renderer.GetOutputWidth()/2)-(size/2),
                               (renderer.GetOutputHeight()/2)-(size/2),
                               size, size),
                          0, SDL_FLIP_NONE);
    }
}

void sdl_waiting::update(bool _active, int _currPlayers, int _totalPlayers) {
    this->active = _active;
    this->currPlayers = _currPlayers;
    this->totalPlayers = _totalPlayers;
    waiting_an.update();
}

