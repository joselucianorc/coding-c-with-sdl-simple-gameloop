#include <stdio.h>
#include <SDL.h>
#include "./constants.h"

int game_is_running = FALSE;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int last_frame_time = 0;

struct ball {
	float x;
	float y;
	float width;
	float height;
} ball;

int initialize_window(void) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL. \n");
		return FALSE;
	}

	window = SDL_CreateWindow(
		  NULL
		, SDL_WINDOWPOS_CENTERED
		, SDL_WINDOWPOS_CENTERED
		, WINDOW_WIDTH
		, WINDOW_HEIGHT
		, SDL_WINDOW_BORDERLESS
	);

	if (!window) {
		fprintf(stderr, "Error creating SDL Window. \n");
		return 0;
	}

	renderer = SDL_CreateRenderer(
		window
		, -1
		, 0
	);

	if (!renderer) {
		fprintf(stderr, "Error creating SDL Renderer.\n");
		return FALSE;
	}

	return TRUE;
}

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_QUIT:
		game_is_running = FALSE;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			game_is_running = FALSE;
		}
	}
}

void setup() {
	ball.x = 20; 
	ball.y = 20; 
	ball.width = 15; 
	ball.height = 15; 
}

void update() {
	//TODO: waste some time / sleep until we reach the frame target time	
	while (!SDL_TICKS_PASSED(SDL_GetTicks(),last_frame_time + FRAME_TARGET_TIME));

	last_frame_time = SDL_GetTicks(); //Time elapsed in miliseconds since init

	ball.x += 2;
	ball.y += 2;
}

void render() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 155);
	SDL_RenderClear(render);

	//Here is where we can start drawing our game objects
	SDL_Rect ball_rect = {
		  (int)ball.x
		, (int)ball.y
		, (int)ball.width
		, (int)ball.height
	};

	SDL_RenderFillRect(renderer, &ball_rect);

	SDL_RenderPresent(renderer);
}

void destroy_window() {
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* args[]) {
	//SDL_Init(SDL_INIT_EVERYTHING);
	game_is_running = initialize_window();

	setup();

	while (game_is_running) {
		process_input();
		update();
		render();
	}

	destroy_window();

	printf("Game Running ... \n");
	return 0;
}