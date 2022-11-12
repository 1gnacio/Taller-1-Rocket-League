#ifndef ROCKET_LEAGUE_SDL_SCOREBOARD_H
#define ROCKET_LEAGUE_SDL_SCOREBOARD_H

#include <SDL2pp/SDL2pp.hh>

class sdl_scoreboard {
private:
    SDL2pp::Font font;
    std::string text;
public:
    explicit sdl_scoreboard(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(const std::string& time, int local_goals, int away_goals);
    ~sdl_scoreboard() = default;
};


#endif //ROCKET_LEAGUE_SDL_SCOREBOARD_H