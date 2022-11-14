//
// Created by igb on 12/11/22.
//

#ifndef SDL_SDL_ANIMATION_H
#define SDL_SDL_ANIMATION_H

#include <SDL2pp/SDL2pp.hh>
#include <vector>

#define FRAME_RATE (1000000.0f/25.0f)

class sdl_animation {
public:
    sdl_animation(SDL2pp::Renderer &renderer, int numFrames, const std::string& path);
    ~sdl_animation();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest, double angle, SDL_RendererFlip &flipType);

    /*
     * Para cambiar el color de la textura.
     * */
    void setColorMod(Uint8 r, Uint8 g, Uint8 b);

private:
    void advanceFrame();
    std::vector<SDL2pp::Texture> textures;
    int currentFrame;
    int numFrames;
    float elapsed;
};


#endif //SDL_SDL_ANIMATION_H
