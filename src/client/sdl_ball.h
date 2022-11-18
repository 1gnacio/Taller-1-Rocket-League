#ifndef ROCKET_LEAGUE_SDL_BALL_H
#define ROCKET_LEAGUE_SDL_BALL_H
#include <SDL2pp/SDL2pp.hh>

class sdl_ball {
private:
    SDL2pp::Texture texture_ball;
    int radius;
    int x;
    int y;
    int angle;
public:
    explicit sdl_ball(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(int x, int y, int angle);
    ~sdl_ball() = default;

};


#endif //ROCKET_LEAGUE_SDL_BALL_H
