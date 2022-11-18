#include "sdl_arena.h"

sdl_arena::sdl_arena(SDL2pp::Renderer &renderer): texture_stadium(renderer, DATA_PATH "/stadium2.png"),
                texture_goal(renderer, DATA_PATH "/goal.png"){}

void sdl_arena::render(SDL2pp::Renderer &renderer) {
    int t_height = renderer.GetOutputHeight();
    int t_width = renderer.GetOutputWidth();
    int size_h= 50 * renderer.GetOutputHeight() /100;
    int size_w= 12 * renderer.GetOutputWidth() /100;
    //Fondo
    renderer.Copy(texture_stadium);
    //Arcos
    //TODO: usar tamaño del server.
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, t_height-size_h, size_w,size_h));
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect((t_width - size_w), t_height-size_h, size_w,size_h), 0,
                  SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
}
