#ifndef HF
#define HF

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 768
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define NUM_TEXTURE 8
#define TEXTURE_WIDTH 128
#define TEXTURE_HEIGHT 128
#define ENEMY_TEX_WIDTH 64
#define ENEMY_TEX_HEIGHT 64
#define SKY_TEXTURE_WIDTH 2048
#define SKY_TEXTURE_HEIGHT 1024
#define PROJ_PLANE_DISTANCE (SCREEN_WIDTH / (2 * tan(FOV / 2)))
#define PLAYER_HEIGHT 32
#define NUM_GUNS 3
#define MAX_ENEMIES 128
#define NUM_SPRINT 6

#define PI 3.1415926536
#define FOV (PI / 3)

#define MAX_KEYBOARD_KEYS 350

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

/**
 * struct App - for SDL data structs
 * @window: pointer to sdl window struct
 * @renderer: pointer to SDL renderer struct
 * @screen_texture: pointer to sdl texture
 * @loadSurface: sdl surface pointer for the loaded surface
 * @convSurface: sdl surface pointer for the converted surface
 * @keyboard: array which holds status of keyboard events
 */
typedef struct App
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *screen_texture;
	SDL_Surface *loadSurface, *convSurface;
	int keyboard[MAX_KEYBOARD_KEYS];
} App;

/**
 * struct Player - player
 * @x: player position in x direction
 * @y: player position in x direction
 * @dir: player viewing angle
 * @gunTextures: array pointer for all gun textures
 * @numGun: indicater which gun is player using
 * @gunTime: counts time before gun changed for again
 */
typedef struct Player
{
	double x;
	double y;
	double dir;
	unsigned int *gunTextures[NUM_GUNS];
	int numGun;
	int gunTime;
} Player;

/**
 * struct Pxl - textures in pixel
 * @pixels: pointer to pixels which is going to rendered
 * @texPixels: wall and floor texture pixels
 * @skyPixels: sky texture pixels
 */
typedef struct Pxl
{
	unsigned int *pixels;
	unsigned int *texPixels[NUM_TEXTURE];
	unsigned int *skyPixels;
} Pxl;

/**
 * struct Map - the map of the game
 * @map: a 2D array map
 * @disp: indicater if player chooses the map to be show or not
 * @mapTime: to avoid repeted keyboard event
 */
typedef struct Map
{
	unsigned int map[MAP_WIDTH][MAP_HEIGHT];
	int disp;
	int mapTime;
} Map_s;

/**
 * struct Buffer - wall distance buffer
 * @distBuffer: wall distance buffer which will be used when sprints are
 * displayed
 */
typedef struct Buffer
{
	double distBuffer[SCREEN_WIDTH];
} Buffer;

#endif
