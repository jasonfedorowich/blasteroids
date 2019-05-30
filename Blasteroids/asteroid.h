#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#pragma once
#define _USE_MATH_DEFINES
#define ASTEROID_MAX_SPEED 10
#define ASTEROID_MIN_SPEED 5


typedef struct Asteroid{
	float sx;
	float sy;
	float heading;
	float speed;
	float twist;
	float rot_velocity;
	float scale;

	int gone;
	Asteroid* next;
	ALLEGRO_COLOR color;

} Asteroid;


Asteroid* create_asteroid();
static void draw_asteroid();