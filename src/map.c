#include "map.h"

/**
 * drawWalls - draw map, walls with black rect and empty space with white
 */
void drawWalls(void)
{
	SDL_Rect rect;
	int stepX = 4, stepY = 4;
	int x, y;

	rect.h = rect.w = 4;
	rect.x = rect.y = 0;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		rect.x = 0;
		for (x = 0; x < MAP_WIDTH; x++)
		{
			SDL_RenderDrawRect(app.renderer, &rect);
			if (Map.map[y][x] != 0)
				SDL_SetRenderDrawColor(app.renderer,
						       3, 37, 76, 255);
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
 * drawRays - draw line starting from player position to wall hit
 */
void drawRays(void)
{
	SDL_Rect rect;
	int hx, hy;
	int wallWidth = 4, wallHeight = 4;
	int px = player.x * wallWidth;
	int py = player.y * wallHeight;
	int lineLength = 8;

	rect.h = rect.w = 2;
	rect.x = px;
	rect.y = py;
	hx = px + lineLength * cos(player.dir);
	hy = py + lineLength * sin(player.dir);
	SDL_SetRenderDrawColor(app.renderer, 228, 34, 64, 255);
	SDL_RenderDrawRect(app.renderer, &rect);
	SDL_RenderFillRect(app.renderer, &rect);
	SDL_RenderDrawLine(app.renderer, px, py, hx, hy);
}

/**
 * drawMap - draw map and what player sees using lines as a ray
 */
void drawMap(void)
{
	if (Map.mapTime > 0)
		Map.mapTime--;
	if (Map.disp)
	{
		drawWalls();
		drawRays();
	}
}
