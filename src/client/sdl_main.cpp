#include "sdl_main.h"

sdl_main::sdl_main(): sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO),
                      window("Rocket League", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   800, 600, SDL_WINDOW_RESIZABLE),
                      renderer(window, -1, SDL_RENDERER_ACCELERATED), ttf(),
                      arena(renderer), scoreboard(renderer), ball(renderer){}

void sdl_main::updateScreen(const Response& response) {
    scoreboard.update("00:01",0,0);
    ball.update(0, 0, 0);
}

void sdl_main::renderScreen() {
    renderer.Clear();
    arena.render(renderer);
    scoreboard.render(renderer);
    //players.render(renderer);
    ball.render(renderer);
    renderer.Present();
}

sdl_main::~sdl_main() {
    //TODO
}
