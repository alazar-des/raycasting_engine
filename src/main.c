#include "main.h"


/**
 * main - function entry
 * description: load map, initialize SDL, load all textures and initialize
 * player position and clear screen and render pixels
 * @argc: not used
 * @argv: not used
 * Return: return 0 if not exit with error.
 */
int main(int argc, char *argv[])
{
	argc = argc, argv = argv;

	parseMap();
	init();
	atexit(cleanup);

	while (1)
	{
		rayCast();
		SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);
		SDL_RenderClear(app.renderer);
		renderAll();
		drawMap();
		SDL_RenderPresent(app.renderer);
		input();
	}
	return (0);
}
