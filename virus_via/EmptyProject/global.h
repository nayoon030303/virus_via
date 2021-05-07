#pragma once
#include "DXUT.h"	
#include "PageManager.h"
#include "GameSystem.h"

/*POS && SIZE*/
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define WIDTH 1024
#define HEIGHT 720
#define START_X WINDOW_WIDTH /2-WIDTH /2
#define START_Y 200 

/*MAP_PROPERTY*/
#define MAP_PROPERTY_EDGE 100
#define MAP_PROPERTY_EMPTY 200
#define MAP_PROPERTY_VISITING 300
#define MAP_PROPERTY_VISIT 400
#define MAP_PROPERTY_TEMP 500

/*Manager*/
extern PageManager pageManager;
extern GameSystem* gameSystem;
/*Map*/

extern int playerMap[WIDTH * HEIGHT];
extern int enemyMap[WIDTH * HEIGHT];
extern int binaryMap[WIDTH * HEIGHT];
extern int map[WIDTH * HEIGHT];

