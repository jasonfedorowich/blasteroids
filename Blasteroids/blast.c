#pragma once
#include "blast.h"
#include "spaceship.h"
#include "blasteroids.h"
#include <math.h>
#include "logic.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include "allegro5/color.h"
#include <allegro5/allegro_primitives.h>

static Blast* blasts[MAX_BLASTS] = { NULL };


//TODO change to dynamic sized array maybe a vector or arraylist where we can more easily
//remove elements
//calling free() on a blast in an array places the
//blast in a different index need to copy to new array best solution
Blast** get_blasts() {
	return blasts;
}


Blast* create_blast(Spaceship* s) {
	Blast* b = malloc(sizeof(Blast));

	if (b == NULL) {
		free(b);
		puts("Cant initialize pointer");
		return NULL;
	}

	b->heading = s->heading;
	float dx = sin(s->heading) * 2;
	
	b->sx = s->sx + dx;
	float dy = -cos(s->heading) * 2;

	b->sy = s->sy + dy;
	b->color = al_map_rgb(255, 0, 0);
	b->speed = BLAST_SPEED;
	b->gone = 1;
	blasts[current_blast] = b;
	b->position_in_tree = current_blast;
	

	current_blast++;

	if (current_blast == MAX_BLASTS) {
		current_blast = 0;
	}

	return b;
}



void ship_blast(Spaceship* s)
{
	create_blast(s);
}

void draw_all_blasts() {
	for (int i = 0; i < current_blast; i++) {
		draw_blast(blasts[i]);
	}
}

void calculate_all_blast_positions() {
	for (int i = 0; i < current_blast; i++) {
		calculate_blast_position(blasts[i]);
	}
}

static void draw_blast(Blast* b) {
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, b->heading);
	al_translate_transform(&transform, b->sx, b->sy);
	al_use_transform(&transform);

	al_draw_line(0, 0, 0, -3, b->color, 2.0f);
} 
/*
static void adjust_array(int pos) {
	for (int i = pos; i < current_blast; i++) {

		blasts[i] = blasts[i + 1];
		blasts[i + 1] = NULL;

	}
	current_blast--;
}
*/
static void destroy_blast(Blast* b) {
	if (b != NULL && b->position_in_tree < MAX_BLASTS && b->position_in_tree > 0) {
		
		blasts[b->position_in_tree] = NULL;
		adjust_array(b->position_in_tree, &blasts, &current_blast);

		free(b);
	}
	return;
}

static void out_of_bounds(Blast* b) {
	if (b->sx > (float)SCREEN_WIDTH) {
		destroy_blast(b);
		return;
	}
	else if (b->sx < 0) {
		destroy_blast(b);
		return;
	}
	else if (b->sy > (float) SCREEN_HEIGHT) {
		destroy_blast(b);
		return;
	}
	else if (b->sy < 0) {
		destroy_blast(b);
		return;
	}

}
static void calculate_blast_position(Blast* b) {
	//calculate the geometrical changes
	float dx = sin(b->heading) * (b->speed);
	float dy = -cos(b->heading) * (b->speed);


	//change positions

	b->sx += dx;
	b->sy += dy;

	out_of_bounds(b);
}



