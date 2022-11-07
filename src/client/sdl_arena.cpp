//
// Created by igb on 06/11/22.
//

#include "sdl_arena.h"

sdl_arena::sdl_arena(SDL2pp::Renderer &renderer): texture_stadium(renderer, DATA_PATH "/stadium2.png"),
                texture_goal(renderer, DATA_PATH "/goal.png"){}

void sdl_arena::render(SDL2pp::Renderer &renderer) {
    int height = renderer.GetOutputHeight();
    int width = renderer.GetOutputWidth();
    renderer.Copy(texture_stadium);
    //TODO: hacerlo escalable.
    renderer.Copy(texture_goal, SDL2pp::Rect(15,0,200,400), SDL2pp::Rect(0,height-180,100,140));
    renderer.Copy(texture_goal, SDL2pp::Rect(15,0,200,400), SDL2pp::Rect(width-100, height-180,100,140), 0, SDL2pp::NullOpt,SDL_FLIP_HORIZONTAL);
}
