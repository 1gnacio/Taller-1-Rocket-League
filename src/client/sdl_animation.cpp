#include "sdl_animation.h"
#include <cassert>
#include <string>

sdl_animation::sdl_animation(SDL2pp::Renderer &renderer, int numFrames, const std::string& path) :
        currentFrame(0), numFrames(numFrames), elapsed(0.0f), loop(true) {
    assert(this->numFrames > 0);
    for (int i = 1; i <= numFrames; ++i) {
        std::string surface = path + std::to_string(i) + ".png";
        this->textures.emplace_back(renderer,
                              //SDL2pp::Surface(surface).SetColorKey(true, 0));
                              SDL2pp::Surface(surface));
    }
}

sdl_animation::~sdl_animation() {
    //TODO
}

void sdl_animation::update(float dt) {
    this->elapsed += dt;
    
    //TODO: ver capaz no hace falta.
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

void sdl_animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, double angle, SDL_RendererFlip &flipType) {
    //std::cout << currentFrame << std::endl;
    if (textures.empty())
        throw std::runtime_error("Vector de texturas empty");

    renderer.Copy(
            textures[currentFrame],
            SDL2pp::NullOpt,
            dst,
            angle,
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}

void sdl_animation::advanceFrame() {
    currentFrame++;
    if(currentFrame >= numFrames)
    {
        currentFrame =0;
    }
    //this->currentFrame = this->currentFrame % this->numFrames;
}

void sdl_animation::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    for (auto & texture : textures) {
        texture.SetColorMod(r, g, b);
    }
}

void sdl_animation::disableLoop() {
    loop = false;
}
