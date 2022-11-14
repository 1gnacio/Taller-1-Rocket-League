#include "sdl_main.h"
#include <chrono>

sdl_main::sdl_main(): sdl(SDL_INIT_VIDEO),
                      window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   900, 500, SDL_WINDOW_RESIZABLE),
                      renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer), scoreboard(renderer), ball(renderer), time(0)
#ifdef SDL_TESTING
                      , my_object(renderer)
#endif
{
#ifndef SDL_TESTING
    players.emplace_back(renderer);
#endif
}

std::string format_duration( std::chrono::milliseconds ms ) {
    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);
    auto hour = duration_cast<hours>(mins);
    mins -= duration_cast<minutes>(hour);
    std::string time = std::to_string(mins.count()) + ":" + std::to_string(secs.count());
    return time;
}

#ifndef SDL_TESTING
void sdl_main::updateScreen(const Response& response) {
    //TODO
    scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    time += UPDATE_TIME;
}
#endif
void sdl_main::renderScreen() {
    renderer.Clear();
    arena.render(renderer);
    scoreboard.render(renderer);
    ball.render(renderer);
#ifndef SDL_TESTING
    for (auto &player:players) {
        player.render(renderer);
    }
#else
    my_object.render(renderer);
#endif
    renderer.Present();
}

sdl_main::~sdl_main() {
    //TODO
}

#ifdef SDL_TESTING
void sdl_main::updateScreen() {
    scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    ball.update(renderer.GetOutputWidth()/2, renderer.GetOutputHeight()-(renderer.GetOutputHeight()/6),0);
    my_object.update(0,renderer.GetOutputHeight()-(renderer.GetOutputHeight()/6), 0, FRAME_RATE);
    time += UPDATE_TIME;
}
#endif