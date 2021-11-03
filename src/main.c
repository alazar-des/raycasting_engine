#include "main.h"

int main(int argc, char *argv[])
{
	argc = argc, argv = argv;

	init();
	atexit(cleanup);
	parseMap();

	while (1)
	{
		input();
		memset(pxl.pixels, 0,
		       SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(unsigned int));
		rayCast();
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
		SDL_RenderClear(app.renderer);
		renderAll();
		drawMap();
		SDL_RenderPresent(app.renderer);
	}
}
