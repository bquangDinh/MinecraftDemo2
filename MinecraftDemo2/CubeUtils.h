#pragma once
#include "CubeType.h"

#define NUM_OF_SIDES 6

#define GRASS_MIN_LIMIT 14
#define GRASS_MAX_LIMIT 15

#define ROCK_MIN_LIMIT 0
#define ROCK_MAX_LIMIT 13

/*Face*/
enum SIDE{
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};

enum DIRECTION {
	FRONT_TO_BACK = 0,
	LEFT_TO_RIGHT = 1,
	TOP_TO_BOTTOM = 2
};

/*Direction*/
#define FRONT_TO_BACK 0
#define LEFT_TO_RIGHT 1
#define TOP_TO_BOTTOM 2

enum VOXEL_TYPE {
	AIR,
	GRASS,
	DIRT,
	ROCK
};

enum VOXEL_TRANSPARENT {
	TRUE = true,
	FALSE = false
};

#define AIR_BLOCK 0
#define GRASS_BLOCK 1
#define ROCK_BLOCK 2

/*Texture*/
#define GRASS_SIDE_TEXTURE "grass_side"
#define GRASS_TOP_TEXTURE "grass_top"
#define GRASS_BOTTOM_TEXTURE "grass_bottom"
