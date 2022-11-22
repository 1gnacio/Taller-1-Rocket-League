#include "sdl_arena.h"

sdl_arena::sdl_arena(SDL2pp::Renderer &renderer): texture_stadium(renderer, DATA_PATH "/stadium2.png"),
                texture_goal(renderer, DATA_PATH "/goal.png"), goal_w(0){}

void sdl_arena::render(SDL2pp::Renderer &renderer) {
    int t_height = renderer.GetOutputHeight();
    int t_width = renderer.GetOutputWidth();
    int size_h= renderer.GetOutputHeight() /2;
    //Fondo
    renderer.Copy(texture_stadium);
    //Arcos
    //TODO: usar tamaño del server.
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, t_height-size_h, goal_w,size_h));
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect((t_width - goal_w), t_height-size_h, goal_w,size_h), 0,
                  SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
}

void sdl_arena::update(int _goal_w) {
    this->goal_w = _goal_w;
}
