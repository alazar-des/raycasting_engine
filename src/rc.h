#include "common.h"
#include "parse.h"

extern Pxl pxl;
extern Player player;
extern Map_s Map;

typedef struct Ray {
	double x, dx;
	double y, dy;
	double dist;
} Ray;

HitCorr hitCorr;
