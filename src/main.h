#ifndef HF_M
#define HF_M

#include "common.h"

extern App app;
extern Pxl pxl;

void init(void);
void rayCast(void);
void input(void);
void parseMap(void);
void renderAll(void);
void cleanup(void);
void drawMap(void);

#endif
