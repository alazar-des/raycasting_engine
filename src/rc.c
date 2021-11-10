#include "rc.h"

/**
 * checkHorizental - check if wall exists when ray intersect with horizental
 *                  axis.
 * @ray_h: struct for storing the intersection point and distance from player
 *          position.
 * @rdir: player direction in radian
 */
void checkHorizental(Ray *ray_h, double rdir)
{
	double rsin = sin(rdir), rcos = cos(rdir);
	int ysub = rsin < 0 ? 1 : 0, hit = 0, e;

	if (rsin != 0)
	{
		if (rsin > 0)
			ray_h->y = ceil(player.y), ray_h->dy = 1;
		else
			ray_h->y = floor(player.y), ray_h->dy = -1;
		ray_h->x = player.x + ((ray_h->y - player.y) * (rcos / rsin));
		ray_h->dx = ray_h->dy * (rcos / rsin);
	}
	else
	{
		ray_h->dist = INFINITY;
		return;
	}
	while (hit == 0)
	{
		if ((ray_h->x >= 0) && (ray_h->x < MAP_HEIGHT) &&
		    (ray_h->y >= 0) && (ray_h->y < MAP_WIDTH))
		{
			e = Map.map[(int) ray_h->y - ysub][(int) ray_h->x];
			if (e != 0 && e < 10)
			{
				ray_h->dist = fabs((player.y - ray_h->y)
						   / rsin);
				ray_h->y -= ysub, hit = 1;
			}
			else
				ray_h->x += ray_h->dx, ray_h->y += ray_h->dy;
		}
		else
		{
			ray_h->dist = INFINITY;
			return;
		}
	}
}

/**
 * checkVertical - check if wall exists when ray intersect with vertical
 *                  axis.
 * @ray_v: struct for storing the intersection point and distance from player
 *          position.
 * @rdir: player direction in radian
 */
void checkVertical(Ray *ray_v, double rdir)
{
	double rsin = sin(rdir), rcos = cos(rdir);
	int xsub = rcos < 0 ? 1 : 0, hit = 0, e;

	if (rcos != 0)
	{
		if (rcos > 0)
			ray_v->x = ceil(player.x), ray_v->dx = 1;
		else
			ray_v->x = floor(player.x), ray_v->dx = -1;
		ray_v->y = player.y + (ray_v->x - player.x) * (rsin / rcos);
		ray_v->dy = ray_v->dx * (rsin / rcos);
	}
	else
	{
		ray_v->dist = INFINITY;
		return;
	}
	while (hit == 0)
	{
		if ((ray_v->x >= 0) && (ray_v->x < MAP_HEIGHT) &&
		    (ray_v->y >= 0) && (ray_v->y < MAP_WIDTH))
		{
			e = Map.map[(int) ray_v->y][(int) ray_v->x - xsub];
			if (e != 0 && e < 10)
			{
				ray_v->dist = fabs((player.x - ray_v->x)
						   / rcos);
				ray_v->x -= xsub, hit = 1;
			}
			else
				ray_v->x += ray_v->dx, ray_v->y += ray_v->dy;
		}
		else
		{
			ray_v->dist = INFINITY;
			return;
		}
	}
}

/**
 * rayCast - casts ray until a ray hits a wall. checks horizental and
 * vertical interception to determine a hit.
*/
void rayCast(void)
{
	Ray ray_h, ray_v;
	double rdir, hfov = FOV / 2, delta_ray = FOV / SCREEN_WIDTH;
	double distance_bn_player_proj = SCREEN_WIDTH / (2 * tan(FOV / 2));
	double dist, height;
	int counter = 0, numWall, offset, side;

	for (rdir = player.dir - hfov; rdir < player.dir + hfov - delta_ray;
	     rdir += delta_ray)
	{
		checkVertical(&ray_v, rdir);
		checkHorizental(&ray_h, rdir);

		if (ray_v.dist < ray_h.dist)
		{
			dist = ray_v.dist * cos(player.dir - rdir);
			numWall = Map.map[(int) ray_v.y][(int) ray_v.x];
			offset = (int) ((ray_v.y - floor(ray_v.y))
					* TEXTURE_WIDTH);
			side = 1;
		}
		else
		{
			dist = ray_h.dist * cos(player.dir - rdir);
			numWall = Map.map[(int) ray_h.y][(int) ray_h.x];
			offset = (int) ((ray_h.x - floor(ray_h.x))
					* TEXTURE_WIDTH);
			side = 0;
		}
		buffer.distBuffer[counter] = dist;
		height = (distance_bn_player_proj / dist);
		generatePixel(counter, height, numWall, offset, rdir, side);
		counter++;
	}
}
