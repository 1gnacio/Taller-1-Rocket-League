#ifndef ROCKET_LEAGUE_SDL_BALL_H
#define ROCKET_LEAGUE_SDL_BALL_H
#include "../libs/libSDL2pp/SDL2pp/SDL2pp.hh"

enum SpecialShot {NORMAL, FLIP, RED, PURPLE, GOLD};

class sdl_ball {
private:
    SDL2pp::Texture texture_ball;
    int width;
    int x;
    int y;
    double angle;
    SpecialShot shot;
public:
    explicit sdl_ball(SDL2pp::Renderer &renderer);
    void render(SDL2pp::Renderer &renderer);
    void update(int _x, int _y, double _angle,
                int radius, bool redShot, bool goldShot,
                bool flipShot, bool purpleShot);
    ~sdl_ball() = default;

};


#endif //ROCKET_LEAGUE_SDL_BALL_H
