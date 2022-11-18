#include "sdl_main.h"
#include <chrono>

sdl_main::sdl_main(): sdl(SDL_INIT_VIDEO),
                      window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   900, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN),
                      renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer), scoreboard(renderer), ball(renderer),
                      convert(MAX_WIDTH, MAX_HEIGHT)
#ifdef SDL_TESTING
                      , my_object(renderer)
#endif
{
#ifndef SDL_TESTING
    players.emplace_back(renderer);
#endif
    //TODO window.SetIcon();
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
void sdl_main::updateScreen(Response& response) {
    //TODO falta obtener el resto de la info.

    for (auto &player: response.getMatchResponses().getMatchResponse().getPlayersResponse().getPlayers()) {
        int car_x = convert.toPixels(player.getPosX(), renderer.GetOutputWidth());
        int car_y = convert.toPixels(player.getPosY(), renderer.GetOutputHeight());
        int car_angle = convert.toDegrees(player.getRotationAngle());
        //TODO ver como crear mas jugadores
        players.back().update(car_x, car_y, car_angle, UPDATE_TIME, player.moving(), player.flying(), player.onTurbo());
    }

    int ball_x = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().getPosX(), renderer.GetOutputWidth());
    int ball_y = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().getPosY(), renderer.GetOutputHeight());
    int ball_angle = convert.toDegrees(response.getMatchResponses().getMatchResponse().getBall().getRotationAngle());
    //int ball_radius = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().g)
    ball.update(ball_x, ball_y, ball_angle, 40);
    int local_goals= response.getMatchResponses().getMatchResponse().getLocalGoals();
    int visitors_goals=response.getMatchResponses().getMatchResponse().getVisitorsGoals();
    int time = response.getMatchResponses().getMatchResponse().getTime();
    scoreboard.update(format_duration((std::chrono::milliseconds)time *1000),local_goals,visitors_goals);
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

void sdl_main::showWindow() {
    window.Show();
}

void sdl_main::hideWindow() {
    window.Hide();
}

#ifdef SDL_TESTING
void sdl_main::updateScreen() {
    scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    ball.update(renderer.GetOutputWidth()/2, renderer.GetOutputHeight()-(renderer.GetOutputHeight()/6),0);
    my_object.update(0,0, 0, FRAME_RATE);
    time += UPDATE_TIME;
}
#endif