#include "initSDL.h"

/**
 * initSDL - initialize SDL library, create window and renderer.
 */
void initSDL(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Couldn't initalize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	app.window = SDL_CreateWindow("3D raycasting Game",
				      SDL_WINDOWPOS_UNDEFINED,
				      SDL_WINDOWPOS_UNDEFINED,
				      SCREEN_WIDTH, SCREEN_HEIGHT,
				      SDL_WINDOW_RESIZABLE);
	if (!app.window)
	{
		printf("Couldn't create window: %s\n", SDL_GetError());
		exit(1);
	}
	app.renderer = SDL_CreateRenderer(app.window, -1,
					  SDL_RENDERER_PRESENTVSYNC |
					  SDL_RENDERER_ACCELERATED);
	if (!app.renderer)
	{
		printf("Couldn't create renderer: %s\n", SDL_GetError());
		exit(1);
	}
	app.screen_texture = SDL_CreateTexture(app.renderer,
					       SDL_PIXELFORMAT_RGBA8888,
					       SDL_TEXTUREACCESS_STREAMING,
					       SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!app.screen_texture)
	{
		printf("Couldn't initialize screen texture: %s\n",
		       SDL_GetError());
		exit(1);
	}

	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

/**
 * cleanup - clean allocated memories, destroy window
 */
void cleanup(void)
{
	int i;

	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();

	if (pxl.pixels != NULL)
	{
		free(pxl.pixels);

		for (i = 0; i < NUM_TEXTURE; i++)
		{
			if (pxl.texPixels[i] != NULL)
				free(pxl.texPixels[i]);
			else
				exit(0);
		}

		if (pxl.skyPixels != NULL)
			free(pxl.skyPixels);
		else
			exit(0);

		for (i = 0; i < NUM_GUNS; i++)
		{
			if (player.gunTextures[i] != NULL)
				free(player.gunTextures[i]);
		}
	}

}
