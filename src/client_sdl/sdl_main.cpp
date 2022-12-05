#include "sdl_main.h"
#include <chrono>

sdl_main::sdl_main(ClientConfigurationAttributes& conf):
            conf(conf),
            sdl(SDL_INIT_VIDEO),
            mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
            AUDIO_CHANNELS, 4096),
            window("Rocket League",
                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 conf.getWindowWidth(), conf.getWindowHeight(),
                 SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN),
            renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
            arena(renderer),  ball(renderer), scoreboard(renderer),
            waiting(renderer), statistics(renderer),
            convert(MAX_WIDTH, MAX_HEIGHT),
            myID(0){ window.SetIcon(SDL2pp::Surface(DATA_PATH "/icon.ico")); }


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
        bool myTurbo = false;
        bool myAcceleration = false;
        bool myJumping = false;
        bool goal = replay;
        for (auto &player:
                response.getMatchResponse().getPlayersResponse().getPlayers()) {
            int car_x = convert.WtoPixels(player.getPosX(),
                                          renderer.GetOutputWidth());
            int car_y = convert.HtoPixels(player.getPosY(),
                                          renderer.GetOutputHeight());
            double car_angle = convert.toDegrees(player.getRotationAngle());
            int id = player.getId();
            bool mainPlayer = false;
            bool localTeam = player.localTeam();
            if (id == myID) {
                turboLeft = player.getRemainingTurbo();
                mainPlayer = true;
                myTurbo = player.onTurbo();
                myJumping = player.flying();
                myAcceleration = player.accelerating();
            }
            int car_w = convert.toPixels(conf.getCarWidth(),
                                         renderer.GetOutputWidth());
            int car_h = convert.toPixels(conf.getCarHeight(),
                                         renderer.GetOutputHeight());
            bool facingLeft = player.isFacingLeft();

            auto it = players.find(id);
            if (it == players.end()) {
                players.try_emplace(id, renderer, localTeam, mainPlayer);
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
        bool ballKicked = response.getMatchResponse().getBall().getHasBeenPunched();
        bool hasBeenPunchedFlipShot = response.getMatchResponse().getBall().getHasBeenPunchedFlipShot();
        bool hasBeenPunchedRedShot = response.getMatchResponse().getBall().getHasBeenPunchedRedShot();
        bool hasBeenPunchedPurpleShot = response.getMatchResponse().getBall().getHasBeenPunchedPurpleShot();
        bool hasBeenPunchedGoldShot = response.getMatchResponse().getBall().getHasBeenPunchedGoldShot();
        ball.update(ball_x, ball_y, ball_angle, ball_width, hasBeenPunchedRedShot, hasBeenPunchedGoldShot,
                    hasBeenPunchedFlipShot, hasBeenPunchedPurpleShot);

        if (ballKicked)
            std::cout << "Ball Kicked" << std::endl;
        sounds.update(goal, myTurbo, myAcceleration, myJumping, ballKicked);
    }

    //TODO: sacar ese 0.7
    arena.update(convert.toPixels(0.7, renderer.GetOutputWidth()),
                 waitingForPlayers, replay, turboLeft);
    bool finishedGame = response.getMatchResponse().isFinished();
    if (finishedGame){
        disableSounds();
        statistics.update(
                response.getMatchResponse().getPlayersResponse().getPlayers());
    }
}

void sdl_main::renderScreen() {
    renderer.Clear();
    arena.render(renderer);
    ball.render(renderer);
    for (auto &player:players) {
        player.second.render(renderer);
    }
    waiting.render(renderer);
    statistics.render(renderer);
    scoreboard.render(renderer);
    sounds.renderSounds(mixer);
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

void sdl_main::enableSounds() {
    sounds.startBackgroundMusic(mixer);
}

void sdl_main::disableSounds() {
    for (int i = 0; i < AUDIO_CHANNELS; ++i) {
        mixer.FadeOutChannel(i, 0);
    }
    mixer.HaltMusic();
}