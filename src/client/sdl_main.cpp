#include "sdl_main.h"

sdl_main::sdl_main(): sdl(SDL_INIT_VIDEO),
                      window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   800, 600, SDL_WINDOW_RESIZABLE),
                      renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer), scoreboard(renderer), ball(renderer), time(0){

    //TODO eliminar.
    players.emplace_back(renderer);
    angle_test =0;
    x_test =0;
    y_test=400;
    dt_test=UPDATE_TIME;
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


void sdl_main::updateScreen(const Response& response) {
    //TODO
    scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    ball.update(x_test, y_test, angle_test);
    players.back().update(x_test,500, 0, FRAME_RATE);
    angle_test += 5;
    x_test += 30;
    y_test -= 10;
    time += UPDATE_TIME;
    if(time == 3){
        players.back().toogleTurbo();
    }
    if(time == 8){
        players.back().toogleTurbo();
    }
}

void sdl_main::renderScreen() {
    renderer.Clear();
    arena.render(renderer);
    scoreboard.render(renderer);
    ball.render(renderer);
    players.back().render(renderer);
    renderer.Present();
}

sdl_main::~sdl_main() {
    //TODO
}
