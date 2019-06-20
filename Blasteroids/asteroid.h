#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include <allegro5/allegro5.h>
#pragma once
#define _USE_MATH_DEFINES
#define ASTEROID_MAX_SPEED 10
#define ASTEROID_MIN_SPEED 5
#define MAX_ASTEROIDS 15

static int current_asteroid = 0;


typedef struct Asteroid {
	float sx;
	float sy;
	float heading;
	float speed;
	float twist;
	float rot_velocity;
	float scale;
	int position_in_tree;
	int gone;
	int has_children;
	struct Asteroid* next;
	ALLEGRO_COLOR color;

} Asteroid;

Asteroid* create_base();
void enrich_asteroid(Asteroid* a);
//static void adjust_array(int pos);
static void draw_asteroid(Asteroid* a);
static void out_of_bounds(Asteroid* a);
void calculate_all_asteroids();
void draw_all_asteroids();