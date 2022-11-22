#include "sdl_main.h"
#include <chrono>

sdl_main::sdl_main(): sdl(SDL_INIT_VIDEO),
                      window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   900, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN),
                      renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer), scoreboard(renderer), ball(renderer),
                      convert(MAX_WIDTH, MAX_HEIGHT), time_ms(0)
#ifdef SDL_TESTING
                      , my_object(renderer)
#endif
{
#ifndef SDL_TESTING
    //players.emplace(0, renderer);
#else
    window.Show();
#endif
    window.SetIcon(SDL2pp::Surface(DATA_PATH "/icon.ico"));
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
    int local_goals= response.getMatchResponses().getMatchResponse().getLocalGoals();
    int visitors_goals=response.getMatchResponses().getMatchResponse().getVisitorsGoals();
    scoreboard.update(format_duration((std::chrono::milliseconds) time_ms),local_goals,visitors_goals);
    time_ms += TIME_UPDATE_MS*2;

    for (auto &player: response.getMatchResponses().getMatchResponse().getPlayersResponse().getPlayers()) {
        int car_x = convert.toPixels(player.getPosX(), renderer.GetOutputWidth());
        int car_y = convert.toPixels(player.getPosY(), renderer.GetOutputHeight());
        double car_angle = convert.toDegrees(player.getRotationAngle());
        int id = player.getId();

        auto it = players.find(id);
        if (it == players.end()){
            players.emplace(id, renderer);
        }
        players.at(id).update(car_x, car_y, car_angle, FRAME_RATE, player.moving(), player.flying(), player.onTurbo());
        if (player.moving())
            std::cout << "ME ESTOY MOVIENDO" << std::endl;
        if(player.flying())
            std::cout << "ESTOY EN EL AIRE" << std::endl;
    }

    int ball_x = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().getPosX(), renderer.GetOutputWidth());
    int ball_y = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().getPosY(), renderer.GetOutputHeight());
    double ball_angle = convert.toDegrees(response.getMatchResponses().getMatchResponse().getBall().getRotationAngle());
    //int ball_radius = convert.toPixels(response.getMatchResponses().getMatchResponse().getBall().g)
    ball.update(ball_x, ball_y, ball_angle, 20);

}
#endif
void sdl_main::renderScreen() {
    renderer.Clear();
    arena.render(renderer);
    scoreboard.render(renderer);
    ball.render(renderer);
#ifndef SDL_TESTING
    for (auto &player:players) {
        player.second.render(renderer);
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
    //scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    ball.update(renderer.GetOutputWidth()/2, renderer.GetOutputHeight()-(renderer.GetOutputHeight()/6),0, 20);
    my_object.update(0,0, 0, FRAME_RATE,true,true,true);
}
#endif