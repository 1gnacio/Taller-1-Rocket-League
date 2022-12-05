#include "sdl_main.h"
#include <chrono>

#include <utility>
#include "../src/constants/logic_values.h"

//TODO: tamaño de ventana por config.
sdl_main::sdl_main(ClientConfigurationAttributes& conf):
            conf(conf),
                    sdl(SDL_INIT_VIDEO),
                      /*mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                            MIX_DEFAULT_CHANNELS, 4096),*/
                      window("Rocket League",
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             conf.getWindowWidth(), conf.getWindowHeight(),
                             SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN),
                     renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer),  ball(renderer), scoreboard(renderer),
                      waiting(renderer), statistics(renderer),
                      convert(MAX_WIDTH, MAX_HEIGHT),
                      myID(0)/*,
                      background_music(DATA_PATH "/background.ogg")*/
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
    //mixer.FadeInMusic(background_music, -1, 2000);
}


#ifndef SDL_TESTING
void sdl_main::updateScreen(Response& response) {
    if (response.dummy()){
        return;
    }
    bool replay = response.getMatchResponse().isReplaying();
    bool waitingForPlayers = response.getMatchResponse().waitingForPlayers();
    waiting.update(waitingForPlayers);
    float turboLeft = 0;
    if (!waitingForPlayers) {
        int local_goals = response.getMatchResponse().getLocalGoals();
        int visitors_goals = response.getMatchResponse().getVisitorsGoals();
        scoreboard.update(convert.timeToString((std::chrono::milliseconds)
                       (response.getMatchResponse().getTime() * 1000)),
                          local_goals, visitors_goals);

        for (auto &player:
                response.getMatchResponse().getPlayersResponse().getPlayers()) {
            int car_x = convert.WtoPixels(player.getPosX(),
                                          renderer.GetOutputWidth());
            int car_y = convert.HtoPixels(player.getPosY(),
                                          renderer.GetOutputHeight());
            double car_angle = convert.toDegrees(player.getRotationAngle());
            int id = player.getId();
            if (id == myID) {
                turboLeft = player.getRemainingTurbo();
            }
            int car_w = convert.toPixels(conf.getCarWidth(),
                                         renderer.GetOutputWidth());
            int car_h = convert.toPixels(conf.getCarHeight(),
                                         renderer.GetOutputHeight());
            bool facingLeft = player.isFacingLeft();

            auto it = players.find(id);
            if (it == players.end()) {
                players.emplace(id, renderer);
            }

            players.at(id).update(car_x, car_y, car_w, car_h, car_angle,
                                  FRAME_RATE, player.moving(), player.flying(),
                                  player.onTurbo(), facingLeft);
        }

        int ball_x = convert.WtoPixels(
                response.getMatchResponse().getBall().getPosX(),
                renderer.GetOutputWidth());
        int ball_y = convert.HtoPixels(
                response.getMatchResponse().getBall().getPosY(),
                renderer.GetOutputHeight());
        double ball_angle = convert.toDegrees(
                response.getMatchResponse().getBall().getRotationAngle());
        int ball_width = 2.0 * convert.toPixels(conf.getBallRadius(),
                                                renderer.GetOutputWidth());
        ball.update(ball_x, ball_y, ball_angle, ball_width);
    }
    arena.update(convert.toPixels(0.7, renderer.GetOutputWidth()),
                 waitingForPlayers, replay, turboLeft);
    bool finishedGame = response.getMatchResponse().isFinished();
    if (finishedGame){
        statistics.update(
                response.getMatchResponse().getPlayersResponse().getPlayers());
    }
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
    waiting.render(renderer);
    statistics.render(renderer);
    renderer.Present();
}

void sdl_main::showWindow() {
    window.Show();
}

void sdl_main::hideWindow() {
    window.Hide();
}

void sdl_main::setID(int id) {
    this->myID = id;
}

#ifdef SDL_TESTING
void sdl_main::updateScreen() {
    //scoreboard.update(format_duration((std::chrono::milliseconds)time),0,0);
    ball.update(renderer.GetOutputWidth()/2,
                renderer.GetOutputHeight()-(renderer.GetOutputHeight()/6),
                0, 20);
    //my_object.updateToFrame(0,0, 0, FRAME_RATE,true,true,true);
}
#endif