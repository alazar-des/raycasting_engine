#ifndef HF
#define HF

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define NUM_TEXTURE 8
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#define PROJ_PLANE_DISTANCE (SCREEN_WIDTH / (2 * tan(FOV / 2)))
#define PLAYER_HEIGHT 32
#define NUM_GUNS 4

#define PI 3.1415926536
#define FOV (PI / 3)

#define MAX_KEYBOARD_KEYS 350

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

/**
 * App -
 */
typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	SDL_Surface *loadSurface, *convSurface;
	int keyboard[MAX_KEYBOARD_KEYS];
} App;

typedef struct Player {
	double x;
	double y;
	double dir;
	SDL_Texture *gunTextures[4];
	int numGun;
	int gunTime;
	int countFireTime;
	int countFireAnim;
} Player;

typedef struct Pxl {
	unsigned int *pixels;
	unsigned int *texPixels[NUM_TEXTURE];
} Pxl;

typedef struct Map {
	unsigned int map[MAP_WIDTH][MAP_HEIGHT];
	int disp;
	int time;
} Map_s;

typedef struct HitCorr
{
	double corr[2][SCREEN_WIDTH];
} HitCorr;

#endif
