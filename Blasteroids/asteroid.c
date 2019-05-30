#include "asteroid.h"
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include "allegro5/color.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "blasteroids.h"
//TODO place asteroid in array
//TODO may need to fix overload


static double random_double_number(double min, double max) {
	return (double)(rand() % (int)(max - min + 1) + min);
}

static int random_number(int min, int max) {
	return (rand() % (max - min + 1)) + min;

}


static double deg_to_rad(int degree) {
	return (double) (degree * M_PI) / 180;
}

static Asteroid* create_base() {
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
	return a;

}
static void enrich_asteroid(Asteroid* a) {
	
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
}

static void enrich_child(Asteroid* a, Asteroid* p) {
	a->sx = p->sx;
	a->sy = p->sy;
	a->heading = p->heading;
	a->rot_velocity = p->rot_velocity;
	a->scale = p->speed;
	a->twist = p->twist;

	a->scale = random_double_number(p->scale / 2, p->scale);
	p->next = a;
}

static void create_child(Asteroid* a) 
{
	Asteroid* node_one = create_base();
	Asteroid* node_two = create_base();

	enrich_child(node_one, a);
	enrich_child(node_two, node_one);


}

static void draw_asteroid(Asteroid *a)
{
	
	
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

}
