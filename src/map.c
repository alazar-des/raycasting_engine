#include "map.h"

/**
 * drawWalls - draw map, walls with black rect and empty space with white
 */
void drawWalls(void)
{
	SDL_Rect rect;
	int stepX = 8, stepY = 8;
	int x, y;

	rect.h = rect.w = 8;
	rect.x = rect.y = 0;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		rect.x = 0;
		for (x = 0; x < MAP_WIDTH; x++)
		{
			SDL_RenderDrawRect(app.renderer, &rect);
			if (Map.map[y][x] != 0)
				SDL_SetRenderDrawColor(app.renderer,
						       0, 255, 255, 255);
			else
				SDL_SetRenderDrawColor(app.renderer,
						       255, 255, 255, 255);
			SDL_RenderFillRect(app.renderer, &rect);
			rect.x += stepX;
		}
		rect.y += stepY;
	}
}

/**
 * drawRay - draw line starting from player position to wall hit
 */
void drawRays(void)
{
	int hx, hy, i;
	int px = player.x * 8;
	int py = player.y * 8;

	SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	for (i = 0; i < SCREEN_WIDTH; i++)
	{
		hx = px + hitCorr.corr[0][i] * cos(hitCorr.corr[1][i]) * 8;
		hy = py + hitCorr.corr[0][i] * sin(hitCorr.corr[1][i]) * 8;
		SDL_RenderDrawLine(app.renderer, px, py, hx, hy);
	}
}

/**
 * drawMap - draw map and what player sees using lines as a ray
 */
void drawMap(void)
{
	if (Map.disp)
	{
		drawWalls();
		drawRays();
	}
}
