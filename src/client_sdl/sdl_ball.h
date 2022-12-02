#ifndef ROCKET_LEAGUE_SDL_BALL_H
#define ROCKET_LEAGUE_SDL_BALL_H
#include "libs/libSDL2pp/SDL2pp/SDL2pp.hh"

class sdl_ball {
private:
    SDL2pp::Texture texture_ball;
    int width;
    int x;
    int y;
    double angle;
public:
    explicit sdl_ball(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(int _x, int _y, double _angle, int radius);
    ~sdl_ball() = default;

};


#endif //ROCKET_LEAGUE_SDL_BALL_H
