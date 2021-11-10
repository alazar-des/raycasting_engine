#include "render.h"

/**
 * generateFloor - generate floor pixels
 * @column: column number
 * @rdir: casted ray direction
 * @end: the point floor casting starts
 */
void generateFloor(int column, double rdir, int end)
{
	int i, r, tx, ty, txs, tys;
	double fx, fy;
	double rcos = cos(rdir), rsin = sin(rdir);
	double dcos = cos(player.dir - rdir);
	double swallDist, wallDist;

	if (end < 0)
		end = SCREEN_HEIGHT;
	for (i = end; i < SCREEN_HEIGHT; i++)
	{
		/** Calculate distance b/n player and floor or ceil */
		r = (i - SCREEN_HEIGHT / 2);
		swallDist = 0.5 * PROJ_PLANE_DISTANCE / r;
		wallDist = swallDist / dcos;

		fx = (player.x + wallDist * rcos);
		fy = (player.y + wallDist * rsin);
		/** floor texture coordinate */
		tx = (int) ((fx - (int) fx) * TEXTURE_WIDTH);
		ty = (int) ((fy - (int) fy) * TEXTURE_HEIGHT);
		/* ceil texture coordinate */
		txs = (int) ((fx / MAP_WIDTH) * SKY_TEXTURE_WIDTH);
		tys = (int) ((fy / MAP_WIDTH) * SKY_TEXTURE_HEIGHT);
		/* generate floor and ceil texture pixels */
		pxl.pixels[column + i * SCREEN_WIDTH] =
			pxl.texPixels[7][tx + ty * TEXTURE_WIDTH];
		pxl.pixels[column + (SCREEN_HEIGHT - (i + 1)) * SCREEN_WIDTH] =
			pxl.skyPixels[txs + tys * SKY_TEXTURE_WIDTH];
	}
}

/**
 * generatePixel - generate pixel/texture of a wall
 * @column: column number
 * @height: the height of the wall
 * @numWall: wall type specifier
 * @x: offset in x position the wall texture pixel to start
 * @rdir: casted ray direction
 * @side: flag if wall is in y-side
 */
void generatePixel(int column, double height, int numWall, int x,
		   double rdir, int side)
{
	int start, end, i;
	double step, y = 0;
	unsigned int color, r, g, b, a;

	step = TEXTURE_HEIGHT / height;
	start = (int) (SCREEN_HEIGHT / 2 - height / 2);
	y = start;
	if (start < 0)
		start = 0;
	end = (int) (height + start);
	if (end > SCREEN_HEIGHT - 1)
		end = SCREEN_HEIGHT - 1;

	y = (start - y) * step;
	for (i = start; i < end; i++)
	{
		color = pxl.texPixels[numWall - 1][x + (int) y * TEXTURE_WIDTH];
		if (side == 1)
		{
			r = ((color & 0xff000000) >> 1) & 0xff000000;
			g = ((color & 0x00ff0000) >> 1) & 0x00ff0000;
			b = ((color & 0x0000ff00) >> 1) & 0x0000ff00;
			a = color & 0x000000ff;
			color = r | g | b | a;
		}
		pxl.pixels[column + i * SCREEN_WIDTH] = color;
		y += step;
	}
	generateFloor(column, rdir, end);
}

/**
 * generatPlayerPixels - generate player gun pixels
 */
void generatPlayerPixels(void)
{
	int i, j, x, y;
	unsigned int color;

	y = (int) (SCREEN_WIDTH - TEXTURE_WIDTH) / 2;
	for (i = 0; i < TEXTURE_HEIGHT; i++)
	{
		x = SCREEN_HEIGHT - TEXTURE_HEIGHT;
		for (j = 0; j < TEXTURE_WIDTH; j++)
		{
			color = player.gunTextures[player.numGun]
				[i + (int) j * TEXTURE_WIDTH];
			x++;
			if (color != 0)
				pxl.pixels[y + x * SCREEN_WIDTH] = color;
		}
		y++;
	}
}

/**
 * renderAll - render the pixels generated
 */
void renderAll(void)
{
	generatPlayerPixels();
	SDL_UpdateTexture(app.screen_texture, NULL, pxl.pixels,
				  SCREEN_WIDTH * 4);
	SDL_RenderCopy(app.renderer, app.screen_texture, NULL, NULL);
	if (player.gunTime > 0)
		player.gunTime--;
}
