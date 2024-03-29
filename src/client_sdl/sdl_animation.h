//
// Created by igb on 12/11/22.
//

#ifndef SDL_SDL_ANIMATION_H
#define SDL_SDL_ANIMATION_H

#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"
#include <vector>
#include <string>


class sdl_animation {
public:
    sdl_animation(SDL2pp::Renderer &renderer, int numFrames,
                  const std::string& path);
    ~sdl_animation() = default;
    void update();
    void updateToFrame(int percentage);
    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest,
                double angle, SDL_RendererFlip flipType);
    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect screct, SDL2pp::Rect dest,
                double angle, SDL_RendererFlip flipType);

    /*
     * Para cambiar el color de la textura.
     * */
    void setColorMod(Uint8 r, Uint8 g, Uint8 b);
    void disableLoop();
    int getWidth();
    int getHeight();
private:
    std::vector<SDL2pp::Texture> textures;
    int currentFrame;
    int numFrames;
    bool loop;
};


#endif //SDL_SDL_ANIMATION_H
