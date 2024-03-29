#include "sdl_main.h"
#include <chrono>

sdl_main::sdl_main(ClientConfigurationAttributes& conf):
            conf(conf),
            sdl(SDL_INIT_VIDEO),
            window("Rocket League",
                 SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                 conf.getWindowWidth(), conf.getWindowHeight(),
                 SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN),
            renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
            mixer(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                  AUDIO_CHANNELS, 4096),
            arena(renderer),  ball(renderer), scoreboard(renderer),
            waiting(renderer), statistics(renderer),
            convert(MAX_WIDTH, MAX_HEIGHT),
            myID(0), showStatistics(false) {
    window.SetIcon(SDL2pp::Surface(DATA_PATH "/icon.ico"));
    if (!conf.enableSound()) {
        mixer.SetMusicVolume(0);
        for (int i = 0; i < AUDIO_CHANNELS; ++i) {
            mixer.SetVolume(i, 0);
        }
    }
}


void sdl_main::updateScreen(Response& response) {
    if (response.dummy()){
        return;
    }
    float turboLeft = 0;

    //Waiting For Players
    bool replay = response.getMatchResponse().isReplaying();
    bool waitingForPlayers = response.getMatchResponse().waitingForPlayers();
    int currPlayers = response.getMatchResponse().getCurrPlayer();
    int totalPlayers = response.getMatchResponse().getRequiredPlayers();
    waiting.update(waitingForPlayers, currPlayers, totalPlayers);

    if (!waitingForPlayers) {
        //Scoreboard
        int local_goals = response.getMatchResponse().getLocalGoals();
        int visitors_goals = response.getMatchResponse().getVisitorsGoals();
        scoreboard.update(convert.timeToString((std::chrono::milliseconds)
                       (response.getMatchResponse().getTime() * 1000)),
                          local_goals, visitors_goals);

        //Players
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
                myAcceleration = player.accelerating();
                mainPlayer = true;
                if (turboLeft != 0){
                    myTurbo = player.onTurbo();
                } else {
                    if (!player.moving()){
                        myAcceleration = false;
                    }
                }
                myJumping = player.flying();
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
            bool onTurbo = player.onTurbo();
            if (player.getRemainingTurbo() == 0){
                onTurbo = false;
            }
            players.at(id).update(car_x, car_y, car_w, car_h,
                                  car_angle, player.moving(),
                                  player.flying(), onTurbo, facingLeft);
        }
        //Ball
        int ball_x = convert.WtoPixels(
                response.getMatchResponse().getBall().getPosX(),
                renderer.GetOutputWidth());
        int ball_y = convert.HtoPixels(
                response.getMatchResponse().getBall().getPosY(),
                renderer.GetOutputHeight());
        double ball_angle = convert.toDegrees(
                response.getMatchResponse().getBall().getRotationAngle());
        int ball_width = 2 * convert.toPixels(conf.getBallRadius(),
                                                renderer.GetOutputWidth());
        bool ballKicked = response.getMatchResponse().getBall().getHasBeenPunched();
        bool hasBeenPunchedFlipShot = response.getMatchResponse().getBall().getHasBeenPunchedFlipShot();
        bool hasBeenPunchedRedShot = response.getMatchResponse().getBall().getHasBeenPunchedRedShot();
        bool hasBeenPunchedPurpleShot = response.getMatchResponse().getBall().getHasBeenPunchedPurpleShot();
        bool hasBeenPunchedGoldShot = response.getMatchResponse().getBall().getHasBeenPunchedGoldShot();
        ball.update(ball_x, ball_y, ball_angle, ball_width, hasBeenPunchedRedShot, hasBeenPunchedGoldShot,
                    hasBeenPunchedFlipShot, hasBeenPunchedPurpleShot);

        //Sounds
        sounds.update(goal, myTurbo, myAcceleration, myJumping, ballKicked);
    }

    //Arena
    arena.update(convert.toPixels(GOAL_WIDTH, renderer.GetOutputWidth()),
                 waitingForPlayers, replay, turboLeft, myID);

    //Statistics
    this->showStatistics = response.getMatchResponse().isFinished();
    if (showStatistics){
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
    if (showStatistics) {
        statistics.render(renderer);
    }
    scoreboard.render(renderer);
    sounds.renderSounds(mixer);
    renderer.Present();
}

void sdl_main::showWindow() {
    window.Show();
}

void sdl_main::hideWindow() {
    this->showStatistics = false;
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