#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <SDL2pp/SDL2pp.hh>

#define FRAME_RATE (1000000.0f/25.0f)

class SdlTexture;
class Area;

class sdl_animation {
   public:
    explicit sdl_animation(SDL2pp::Texture &texture);
    ~sdl_animation() = default;
    void update(float dt);
    void render(SDL2pp::Renderer &renderer, SDL2pp::Rect dest, SDL_RendererFlip &flipType);


   private:
    void advanceFrame();
    /** SDL texture of the raw image. */
    SDL2pp::Texture &texture;
    /** Current animation frame. */
    int currentFrame;
    /** Total number of frames in the sprite. */
    int numFrames;
    /** Size of the sprite (height and width). */
    int size;
    /** Time elapsed since last update. */
    float elapsed;
};

#endif  //__ANIMATION_H__
