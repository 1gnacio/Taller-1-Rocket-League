//
// Created by igb on 04/12/22.
//

#include "sdl_statistics.h"

sdl_statistics::sdl_statistics(SDL2pp::Renderer &renderer):
font(DATA_PATH "/Vera.ttf", 50),
background(renderer, DATA_PATH "/football_background.png"),
activate(false) {}

void sdl_statistics::render(SDL2pp::Renderer &renderer) {
    if (activate){
        int y0 = (renderer.GetOutputHeight()/10)*2;
        int height = (renderer.GetOutputHeight()-(y0*2))/text.size();
//        renderer.FillRect(0, y0,
//                          renderer.GetOutputWidth(),
//                          renderer.GetOutputHeight());
        renderer.Copy(background, SDL2pp::NullOpt, SDL2pp::Rect(
                0, 0, renderer.GetOutputWidth(), renderer.GetOutputHeight()));
        for (std::size_t i = 0; i < text.size(); ++i) {
            text[i].insert(text[i].end(), 30 - text[i].size(), ' ');
            SDL2pp::Texture text_sprite(
                    renderer,
                    font.RenderText_Blended(text[i],
                                            SDL_Color{0, 0, 0, 255}));

            renderer.Copy(text_sprite, SDL2pp::NullOpt,
                          SDL2pp::Rect(renderer.GetOutputWidth()/8, y0+(i*height),
                                       renderer.GetOutputWidth() - ((renderer.GetOutputWidth()/8)*2),
                                       height));
        }
    }
}

void sdl_statistics::update(std::vector<PlayerResponse> _players) {
    text.clear();
    this->activate = true;
    std::string local;
    text.emplace_back("     LOCAL");
    text.emplace_back("ID   GOALS   ASSISTS   SAVES");
    for (auto player: _players) {
        if (player.localTeam()) {
            local.clear();
            local = std::to_string(player.getId()) + "     ";
            local += std::to_string(player.getGoals()) + "        ";
            local += std::to_string(player.getAssists()) + "        ";
            local += std::to_string(player.getSaves());
            text.emplace_back(local);
        }
    }
    text.emplace_back(" ");
    text.emplace_back(" ");
    text.emplace_back("     VISITORS");
    text.emplace_back("ID   GOALS   ASSISTS   SAVES");
    for (auto player: _players) {
        if (!player.localTeam()) {
            local.clear();
            local = std::to_string(player.getId()) + "     ";
            local += std::to_string(player.getGoals()) + "        ";
            local += std::to_string(player.getAssists()) + "        ";
            local += std::to_string(player.getSaves());
            text.emplace_back(local);
        }
    }
}
