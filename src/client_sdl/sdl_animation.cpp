#include "sdl_animation.h"
#include <cassert>
#include <string>

sdl_animation::sdl_animation(SDL2pp::Renderer &renderer, int numFrames,
                             const std::string& path) :
        currentFrame(0), numFrames(numFrames), elapsed(0.0f), loop(true) {
    assert(this->numFrames > 0);
    for (int i = 1; i <= numFrames; ++i) {
        std::string surface = path + std::to_string(i) + ".png";
        this->textures.emplace_back(renderer,
                              //SDL2pp::Surface(surface).SetColorKey(true, 0));
                              SDL2pp::Surface(surface));
    }

    if (textures.empty())
        throw std::runtime_error("Vector de texturas vacío");
}

void sdl_animation::update(unsigned int dt) {
    this->elapsed += dt;
    //TODO: hacerlo con la cantidad de frames.
    while (this->elapsed > FRAME_RATE) {
        this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
    this->advanceFrame();
}

void sdl_animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst,
                           double angle, SDL_RendererFlip flipType) {
    renderer.Copy(
            textures[currentFrame],
            SDL2pp::NullOpt,
            dst,
            angle,
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType);
}

void sdl_animation::advanceFrame() {
    currentFrame++;
    if (currentFrame >= numFrames)
    {
        currentFrame =0;
    }
}

void sdl_animation::setColorMod(Uint8 r, Uint8 g, Uint8 b) {
    for (auto & texture : textures) {
        texture.SetColorMod(r, g, b);
    }
}

void sdl_animation::disableLoop() {
    loop = false;
}

void sdl_animation::updateToFrame(int percentage) {
    currentFrame = std::abs((percentage * (numFrames-1))/100);
    //std::cout << "CurrFrame= " << currentFrame << std::endl;
}

void sdl_animation::render(SDL2pp::Renderer &renderer, SDL2pp::Rect screct,SDL2pp::Rect dst,
                           double angle, SDL_RendererFlip flipType) {
    if (textures.empty())
        throw std::runtime_error("Vector de texturas vacío");

    renderer.Copy(
            textures[currentFrame],
            screct,
            dst,
            angle,
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType);
}

int sdl_animation::getWidth() {
    return textures[0].GetWidth();
}

int sdl_animation::getHeight() {
    return textures[0].GetHeight();
}
