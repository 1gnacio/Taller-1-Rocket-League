#include <iostream>
#include <exception>

#include <SDL2pp/SDL2pp.hh>

using namespace SDL2pp;


int main() try {


	SDL sdl(SDL_INIT_VIDEO);

	Window window("SDL2pp demo",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			800, 480,
			SDL_WINDOW_RESIZABLE);

	Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);





	Texture spriteStadium(renderer, DATA_PATH "/stadium.png");
	//Texture spritesCar(renderer, Surface(DATA_PATH "/car.png")
	//		.SetColorKey(true,1200));
	Texture spritesCar(renderer, DATA_PATH "/car.png");
	spritesCar.SetColorMod(255,60,60);

	spritesCar.SetBlendMode(SDL_BLENDMODE_BLEND);
	spritesCar.SetAlphaMod(255);

	int run_phase = -1;      // run animation phase
	float position = 0.0;    // player position
	bool is_running_right = false;
	bool is_running_left = false;

	unsigned int prev_ticks = SDL_GetTicks();
	int src_x = 30, src_y = 35;

	while (1) {
		SDL_Event event;

		unsigned int frame_ticks = SDL_GetTicks();
		unsigned int frame_delta = frame_ticks - prev_ticks;
		prev_ticks = frame_ticks;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			} else if (event.type == SDL_KEYDOWN) {
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE: case SDLK_q:
					return 0;
				case SDLK_RIGHT: is_running_right = true; break;
				case SDLK_LEFT: is_running_left = true; break;
				}
			} else if (event.type == SDL_KEYUP) {
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT: is_running_right = false; break;
				case SDLK_LEFT: is_running_left = false; break;
				}
			}
		}

		if (is_running_right) {
			position += frame_delta * 0.2;
			run_phase = (frame_ticks / 100) % 8;
		} else {
			run_phase = 0;
		}

		if (is_running_left) {
			position -= frame_delta * 0.2;
			run_phase = (frame_ticks / 100) % 8;
		} else {
			run_phase = 0;
		}

		
		// If player passes past the right side of the window, wrap him
		// to the left side
		if (position > renderer.GetOutputWidth())
			position = -50;
		else if(position < -50)
			position = renderer.GetOutputWidth();


		renderer.Clear();

		int vcenter = renderer.GetOutputHeight() / 2; // Y coordinate of window center


		 // by default, standing sprite
		if (is_running_right) {
			// one of 8 run animation sprites
			src_y = 155;
		} else if(is_running_left){
			src_y = 35;

		}

		
		renderer.Copy(spriteStadium);
		renderer.Copy(
				spritesCar,
				Rect(30, 155, 175, 50),
				Rect(700, vcenter+120, 100, 40)
		);
		renderer.Copy(
				spritesCar,
				Rect(src_x, src_y, 175, 50),
				Rect((int)position, vcenter+120, 100, 40)
		);

		renderer.Present();

		SDL_Delay(1);

	}


	return 0;

} catch (std::exception& e) {
	// If case of error, print it and exit with error
	std::cerr << e.what() << std::endl;
	return 1;
}
