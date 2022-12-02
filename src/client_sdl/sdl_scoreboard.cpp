#include "sdl_scoreboard.h"

sdl_scoreboard::sdl_scoreboard(SDL2pp::Renderer &renderer):
    font(DATA_PATH "/Vera.ttf", 50){
    update("00:00", 0, 0);
}
//TODO: hacerlo más lindo.

void sdl_scoreboard::update(const std::string& time,
                            int local_goals, int visitors_goals) {
    text = "LOCAL: " + std::to_string(local_goals) +
            "   " + time + "   VISITORS: " + std::to_string(visitors_goals);
}

void sdl_scoreboard::render(SDL2pp::Renderer &renderer) {
    SDL2pp::Texture text_sprite(
            renderer,
            font.RenderText_Blended(text, SDL_Color{255, 255, 255, 255}));
    int t_width=renderer.GetOutputWidth()/2;
    int t_height=renderer.GetOutputHeight()/10;
    int vcenter = (renderer.GetOutputWidth()/2) - (t_width/2);
    renderer.FillRect(vcenter, 0, vcenter+t_width, t_height);
    //renderer.SetDrawColor(255,0,0,255);
    renderer.Copy(text_sprite, SDL2pp::NullOpt,
                  SDL2pp::Rect(vcenter, 0, t_width, t_height));
}
