#include "sdl_scoreboard.h"

sdl_scoreboard::sdl_scoreboard(SDL2pp::Renderer &renderer): font(DATA_PATH "/Vera.ttf", 30){
    update("00:00", 0, 0);
}
//TODO: hacerlo más lindo.

void sdl_scoreboard::update(const std::string& time, int local_goals, int away_goals) {
    text = "LOCAL: " + std::to_string(local_goals) + "   " + time + "   AWAY: " + std::to_string(away_goals);
}

void sdl_scoreboard::render(SDL2pp::Renderer &renderer) {
    SDL2pp::Texture text_sprite(
            renderer,
            font.RenderText_Blended(text, SDL_Color{255, 165, 0, 255})
    );
    int vcenter = (renderer.GetOutputWidth()/2) - (text_sprite.GetWidth()/2);
    renderer.Copy(text_sprite, SDL2pp::NullOpt, SDL2pp::Rect(vcenter, 0, text_sprite.GetWidth(), text_sprite.GetHeight()));
}
