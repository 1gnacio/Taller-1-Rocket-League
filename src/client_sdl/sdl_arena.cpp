#include "sdl_arena.h"

sdl_arena::sdl_arena(SDL2pp::Renderer &renderer):
    texture_stadium(renderer, DATA_PATH "/stadium2.png"),
    texture_goal(renderer, DATA_PATH "/goal.png"), goal_w(0),
    font(DATA_PATH "/Vera.ttf", 80),
    waitingForPlayer(false), replay(false){}

void sdl_arena::render(SDL2pp::Renderer &renderer) {
    int t_height = renderer.GetOutputHeight();
    int t_width = renderer.GetOutputWidth();
    int size_h= renderer.GetOutputHeight() /2;
    //Fondo
    renderer.Copy(texture_stadium);
    //Arcos
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect(0, t_height-size_h, goal_w,size_h));
    renderer.Copy(texture_goal, SDL2pp::NullOpt,
                  SDL2pp::Rect((t_width - goal_w), t_height-size_h,
                               goal_w,size_h),
                  0,SDL2pp::NullOpt, SDL_FLIP_HORIZONTAL);
    //Waiting for players
    if (waitingForPlayer){
        renderText(renderer, "WAITING FOR PLAYERS...",
                   renderer.GetOutputWidth()/2, renderer.GetOutputHeight()/2);
    } else if (replay) {
        renderText(renderer, "REPLAY",renderer.GetOutputWidth()/2,
                   renderer.GetOutputHeight()/2);
    }
}

void sdl_arena::update(int _goal_w, bool _waitingForPlayer, bool _replay) {
    this->goal_w = _goal_w;
    this->waitingForPlayer = _waitingForPlayer;
    this->replay = _replay;

    if (waitingForPlayer or replay){
        texture_goal.SetColorMod(80,80,80);
        texture_stadium.SetColorMod(80,80,80);
    } else{
        texture_goal.SetColorMod(255,255,255);
        texture_stadium.SetColorMod(255,255,255);
    }
}

void sdl_arena::renderText(SDL2pp::Renderer &renderer,
                   const std::string& text, int x, int y) {
    SDL2pp::Texture texture_text(renderer,
                                 font.RenderText_Blended(text,
                                     SDL_Color{255, 255, 255, 255}));
    int text_width=renderer.GetOutputWidth()/2;
    int text_height=renderer.GetOutputHeight()/10;

    renderer.FillRect(x-(text_width/2), y-(text_height/2),
                      x+(text_width/2), y+(text_height/2));
    renderer.Copy(texture_text, SDL2pp::NullOpt,
                  SDL2pp::Rect(x-(text_width/2), y-(text_height/2),
                               text_width, text_height));
}
