#pragma once

#define CHUNK_SIZE 16

#define AIR_BLOCK 0
#define GRASS_BLOCK 1
#define ROCK_BLOCK 2

#define GRASS_MIN_LIMIT 3
#define GRASS_MAX_LIMIT 5

#define ROCK_MIN_LIMIT 0
#define ROCK_MAX_LIMIT 2

#define FRONTSIDE 0
#define BACKSIDE 1
#define LEFTSIDE 2
#define RIGHTSIDE 3
#define TOPSIDE 4
#define BOTTOMSIDE 5

typedef struct {
	int x;
	int y;
	int z;
} Location;

typedef struct {
	unsigned int type;
} CubeType;

typedef struct {
	Location cubeLocation;
	CubeType cubeType;
} CubeData;