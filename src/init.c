#include "init.h"

/**
 * getPixels - Load wall textures and Read their pixels.
 * @filename: image path/filename
 * @pixels: memory address to which the pixels will be written
 */
void getPixels(char *filename, unsigned int *pixels)
{
	app.loadSurface = IMG_Load(filename);
	if (app.loadSurface == NULL)
	{
		printf("Couldn't load surface: %s\n", SDL_GetError());
		exit(1);
	}
	app.convSurface = SDL_ConvertSurfaceFormat(app.loadSurface,
						   SDL_PIXELFORMAT_RGBA8888,
						   0);
	if (app.convSurface == NULL)
	{
		printf("Unable to convert loaded surface: %s\n",
		       SDL_GetError());
		exit(1);
	}
	memcpy(pixels, app.convSurface->pixels,
	       app.convSurface->pitch * app.convSurface->h);

	SDL_FreeSurface(app.loadSurface);
	SDL_FreeSurface(app.convSurface);

}

/**
 * getWallPixels - Load wall textures and Read their pixels.
 */
void getWallPixels(void)
{
	char *filename[NUM_TEXTURE] = {
		"res/doors_trapdoor_steel.png", "res/default_stone_brick.png",
		"res/bluestone.png",
		"res/colorstone.png", "res/default_mossycobble.png",
		"res/colorstone.png", "res/bluestone.png", "res/grass.png"
	};
	int i;

	for (i = 0; i < NUM_TEXTURE; i++)
	{
		pxl.texPixels[i] = malloc(TEXTURE_WIDTH * TEXTURE_HEIGHT *
				      sizeof(unsigned int));
		memset(pxl.texPixels[i], 0, TEXTURE_WIDTH * TEXTURE_HEIGHT *
		       sizeof(unsigned int));

		getPixels(filename[i], pxl.texPixels[i]);
	}
}

/**
 * getSkyPixels - Load sky textures and Read their pixels.
 */
void getSkyPixels(void)
{
	char *filename = "res/sky.jpg";

	pxl.skyPixels = malloc(SKY_TEXTURE_WIDTH * SKY_TEXTURE_HEIGHT *
					  sizeof(unsigned int));
	memset(pxl.skyPixels, 0, SKY_TEXTURE_WIDTH * SKY_TEXTURE_HEIGHT *
	       sizeof(unsigned int));

	getPixels(filename, pxl.skyPixels);
}

/**
 * initPlayer - initialze player position and load gun textures
 */
void initPlayer(void)
{
	char *filename[NUM_GUNS] = {
		"res/guns/gun1a.png", "res/guns/gun4.png", "res/guns/gun5a.png"
	};
	int i;

	player.x = 11.5;
	player.y = 22;
	player.dir = 1.5 * PI;
	player.numGun = 0;
	player.gunTime = 10;

	for (i = 0; i < NUM_GUNS; i++)
	{
		player.gunTextures[i] = malloc(TEXTURE_WIDTH * TEXTURE_HEIGHT *
				      sizeof(unsigned int));
		memset(player.gunTextures[i], 0,
		       TEXTURE_WIDTH * TEXTURE_HEIGHT * sizeof(unsigned int));
		getPixels(filename[i], player.gunTextures[i]);
	}
}

/**
 * init - initialize SDL and load texture pixels
 */
void init(void)
{
	initSDL();
	pxl.pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT *
			    sizeof(unsigned int));

	getWallPixels();
	getSkyPixels();
	initPlayer();
}
