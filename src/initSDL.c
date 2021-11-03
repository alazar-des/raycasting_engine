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
 * getPixels - Load wall textures and Read their pixels.
 */
void getWallPixels(void)
{
	char *filename[NUM_TEXTURE] = {
		"res/wood.png", "res/purplestone.png", "res/bluestone.png",
		"res/colorstone.png", "res/colorstone.png",
		"res/colorstone.png", "res/bluestone.png", "res/redbrick.png"
	};
	int i;

	for (i = 0; i < NUM_TEXTURE; i++)
	{
		pxl.texPixels[i] = malloc(TEXTURE_WIDTH * TEXTURE_HEIGHT *
				      sizeof(unsigned int));
		memset(pxl.texPixels[i], 0, TEXTURE_WIDTH * TEXTURE_HEIGHT *
		       sizeof(unsigned int));

		app.loadSurface = IMG_Load(filename[i]);
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
		memcpy(pxl.texPixels[i], app.convSurface->pixels,
		       app.convSurface->pitch * app.convSurface->h);
	}
}

/**
 * initPlayer - initialze player position and load gun textures
 */
void initPlayer(void)
{
	char *filename[NUM_GUNS] = {
		"res/g1.png", "res/g2.png",
		"res/g3.png", "res/g4.png"
	};
	int i;

	player.x = 11.5;
	player.y = 22;
	player.dir = 1.5 * PI;
	player.numGun = 0;
	player.countFireTime = 10;
	player.countFireAnim = 0;
	player.gunTime = 10;

	for (i = 0; i < NUM_GUNS; i++)
	{
		player.gunTextures[i] = IMG_LoadTexture(app.renderer,
						       filename[i]);
		if (player.gunTextures[i] == NULL)
		{
			printf("Couldn't load surface: %s\n", SDL_GetError());
			exit(1);
		}
	}
}

/**
 * cleanup - clean allocated memories, destroy window
 */
void cleanup(void)
{
	int i;

	if (pxl.pixels != NULL)
		free(pxl.pixels);

	for (i = 0; i < NUM_TEXTURE; i++)
	{
		if (pxl.texPixels[i] != NULL)
			free(pxl.texPixels[i]);
	}

	SDL_FreeSurface(app.loadSurface);
	SDL_FreeSurface(app.convSurface);
	SDL_DestroyRenderer(app.renderer);
	SDL_DestroyWindow(app.window);
	SDL_Quit();
}

void init(void)
{
	initSDL();
	pxl.pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT *
			    sizeof(unsigned int));

	getWallPixels();
	initPlayer();
}
