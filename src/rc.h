#ifndef HF_RC
#define HF_RC

#include "common.h"
#include "parse.h"

extern Pxl pxl;
extern Player player;
extern Map_s Map;

/**
 * struct Ray - casted ray
 * @x: ray position in x dir
 * @dx: change of ray in x dir
 * @y: ray pos in y dir
 * @dy: change of ray in y dir
 * @dist: distance a ray moves to hit a wall
 */
typedef struct Ray
{
	double x, dx;
	double y, dy;
	double dist;
} Ray;

Buffer buffer;

void generatePixel(int column, double height, int numWall, int x,
		   double rdir, int side);

#endif
