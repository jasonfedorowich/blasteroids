#include "asteroid.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include "allegro5/color.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "blasteroids.h"
#include <stdio.h>
#include "logic.h"
//TODO place asteroid in array
//TODO may need to fix overload

static Asteroid* asteroids[MAX_ASTEROIDS] = { NULL };



static double deg_to_rad(int degree) {
	return (double) (degree * M_PI) / 180;
}

 Asteroid* create_base() {
	Asteroid* a = malloc(sizeof(Asteroid));

	if (a == NULL) {
		free(a);
		puts("Cant initialize pointer");
		return NULL;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	ALLEGRO_COLOR color = al_map_rgb_f(1, 0, 0);
	a->color = color;
	a->gone = 1;
	asteroids[current_asteroid] = a;
	a->position_in_tree = current_asteroid;
	printf("%d\n", a->position_in_tree);
	printf("%d\n", current_asteroid);

	current_asteroid++;
	return a;

}
 void enrich_asteroid(Asteroid* a) {
	
	//randomize logic goes here
	//TODO replace with random number
	if (random_number(0, 1)) {
		if (random_number(0, 1)) {
			a->sx = SCREEN_WIDTH;
			a->sy = random_number(0, SCREEN_HEIGHT);
		}
		else {
			a->sx = 0;
			a->sy = random_number(0, SCREEN_HEIGHT);
		}


	}
	else {
		if (random_number(0, 1)) {
			a->sy = SCREEN_HEIGHT;
			a->sx = random_number(0, SCREEN_WIDTH);
		}
		else {
			a->sy = 0;
			a->sx = random_number(0, SCREEN_WIDTH);
		}
	}
	a->twist = 0;
	a->rot_velocity = random_double_number(0, 0.1);
	a->heading = random_number(deg_to_rad(0), deg_to_rad(360));
	a->speed = random_number(ASTEROID_MIN_SPEED, ASTEROID_MAX_SPEED);
	a->scale = random_double_number(0.6, 1.4);
	a->next = NULL;
	a->has_children = 0;
	return;
}

static void enrich_child(Asteroid* a, Asteroid* p) {
	a->sx = p->sx;
	a->sy = p->sy;
	a->heading = -p->heading;
	a->rot_velocity = p->rot_velocity;
	a->speed = -p->speed;
	a->twist = -p->twist;
	a->has_children = 0;
	a->scale = random_double_number(p->scale / 2, p->scale);
	p->next = a;
	return;
}

static void create_child(Asteroid* a) 
{
	Asteroid* node_one = create_base();
	Asteroid* node_two = create_base();
	a->has_children = 1;
	enrich_child(node_one, a);
	enrich_child(node_two, node_one);
	return;

}

static void draw_asteroid(Asteroid *a)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, a->twist);
	al_translate_transform(&transform, a->sx, a->sy);
	al_use_transform(&transform);
	al_scale_transform(&transform, a->scale, a->scale);

	al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line(-25, 5, -25, -10, a->color, 2.0f);
	al_draw_line(-25, -10, -5, -10, a->color, 2.0f);
	al_draw_line(-5, -10, -10, -20, a->color, 2.0f);
	al_draw_line(-10, -20, 5, -20, a->color, 2.0f);
	al_draw_line(5, -20, 20, -10, a->color, 2.0f);
	al_draw_line(20, -10, 20, -5, a->color, 2.0f);
	al_draw_line(20, -5, 0, 0, a->color, 2.0f);
	al_draw_line(0, 0, 20, 10, a->color, 2.0f);
	al_draw_line(20, 10, 10, 20, a->color, 2.0f);
	al_draw_line(10, 20, 0, 15, a->color, 2.0f);
	al_draw_line(0, 15, -20, 20, a->color, 2.0f);
	return;
}

static void free_asteroid(Asteroid* a) {

}

static void destroy_asteroid(Asteroid* a) {
	if (a != NULL && a->position_in_tree < MAX_ASTEROIDS && a->position_in_tree > 0) {
		printf("%d\n", a->position_in_tree);	
		adjust_array(a->position_in_tree);
		for (; a != NULL; a = a->next) {
			free(a);
		}
		asteroids[a->position_in_tree] = NULL;
	}
	return;

}


void out_of_bounds(Asteroid* a)
{
	if (a->sx > ((float)SCREEN_WIDTH)+10.0f) {
		destroy_asteroid(a);
		return;
	}
	else if (a->sx < (0.0f-10.0f)) {
		destroy_asteroid(a);
		return;
	}
	else if (a->sy > ((float) SCREEN_HEIGHT)+10.0f) {
		destroy_asteroid(a);
		return;
	}
	else if (a->sy < (0.0f-10.0f)) {
		destroy_asteroid(a);
		return;
	}
}
static void calculate_asteroid_position(Asteroid* a) {
	//calculate the geometrical changes
	float dx = sin(a->heading) * (a->speed);
	float dy = -cos(a->heading) * (a->speed);


	//change positions

	a->sx += dx;
	a->sy += dy;

	out_of_bounds(a);
}
static void calculate_all_collisions() {
	for (int i = 0; i < current_asteroid; i++) {
		Asteroid* a = asteroids[i];
		for (; a != NULL; a = a->next) {
			is_collision(a);
		}
		
	}
}

static void create_all_children() {
	for (int i = 0; i < current_asteroid; i++) {
		Asteroid* a = asteroids[i];
		if (a->gone && !a->next) {
			create_child(a);
			continue;
		}

	}
}

static void is_destroyed(Asteroid *a) {
	if (!a->gone && !a->next->gone) {
		destroy_asteroid(a);
	}
}

static void check_if_destroyed() {
	for (int i = 0; i < current_asteroid; i++) {
		is_destroyed(asteroids[i]);
	}
	return;
}

void calculate_all_asteroids()
{
	calculate_all_collisions();
	create_all_children();
	check_if_destroyed();
}


