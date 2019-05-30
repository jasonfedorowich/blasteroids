#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include <allegro5/allegro5.h>
#pragma once

static float ACCELERATE_SHIP = 2.0f;
static float MAX_SPEED = 50.0f;
static float ROTATE_DELTA = 0.13f;
static float DECELERATE_SHIP = 2.0f;


typedef struct {
	float sx;
	float sy;
	float heading;
	float speed;
	int gone;
	ALLEGRO_COLOR color;

} Spaceship ;

Spaceship* createship();
void update_ship_location(float* x, float* y);
void draw_spaceship(Spaceship* ship);

void rotate_ship(Spaceship* s, ALLEGRO_EVENT* event);

void ship_accelerate(Spaceship* s);


void ship_decelerate(Spaceship* s);

void ship_position(Spaceship* s);
void destroy_ship(Spaceship* s); 