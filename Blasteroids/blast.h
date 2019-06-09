#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/color.h"
#include "spaceship.h"
#pragma once
typedef struct Blast {
	float sx;
	float sy;
	float heading;
	float speed;
	int gone;
	int position_in_tree;
	ALLEGRO_COLOR color;

} Blast;
#define BLAST_SPEED (MAX_SPEED * 1.5)

#define MAX_BLASTS 40
static int current_blast = 0;

Blast* create_blast(Spaceship *s);
void ship_blast(Spaceship* s);
static void calculate_blast_position(Blast* b);
static void out_of_bounds(Blast* b);
static void destroy_blast(Blast* b);
static void adjust_array(int pos);
static void draw_blast(Blast* b);
void draw_all_blasts();
void calculate_all_blast_positions();
Blast** get_blasts();