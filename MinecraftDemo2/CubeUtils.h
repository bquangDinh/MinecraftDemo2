#pragma once
#include "CubeType.h"

#define CHUNK_SIZE 60
#define NUM_OF_SIDES 6

#define GRASS_MIN_LIMIT 14
#define GRASS_MAX_LIMIT 15

#define ROCK_MIN_LIMIT 0
#define ROCK_MAX_LIMIT 13

/*Face*/
#define FRONTSIDE 0
#define BACKSIDE 1
#define RIGHTSIDE 2
#define LEFTSIDE 3
#define TOPSIDE 4
#define BOTTOMSIDE 5

/*Direction*/
#define FRONT_TO_BACK 0
#define LEFT_TO_RIGHT 1
#define TOP_TO_BOTTOM 2

#define AIR_BLOCK 0
#define GRASS_BLOCK 1
#define ROCK_BLOCK 2

/*Texture*/
#define GRASS_SIDE_TEXTURE "grass_side"
#define GRASS_TOP_TEXTURE "grass_top"
#define GRASS_BOTTOM_TEXTURE "grass_bottom"
