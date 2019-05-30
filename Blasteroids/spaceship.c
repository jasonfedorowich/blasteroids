#include "spaceship.h"
#include <stdio.h>
#include "../packages/Allegro.5.2.5.2/build/native/include/allegro5/transformations.h"
#include "allegro5/color.h"
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "blasteroids.h"

Spaceship* createship()
{
	Spaceship* s =  malloc(sizeof(Spaceship));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	
	ALLEGRO_COLOR shipcolor = al_map_rgb_f(1, 0, 0);
	if (s == NULL) {
		free(s);
		puts("Cant initialize pointer");
		return NULL;
	}
	//s->gone = 1;
	s->speed = 0.0;
	s->heading = 0.0; // radians
	s->sx = 10.0;
	s->sy = 10.0;
	s->color = shipcolor;
	return s;
}

void draw_spaceship(Spaceship* ship)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform(&transform);
	al_rotate_transform(&transform, ship->heading);
	al_translate_transform(&transform, ship->sx, ship->sy);
	al_use_transform(&transform);

	al_draw_line(-8, 9, 0, -11, ship->color, 3.0f);
	al_draw_line(0, -11, 8, 9, ship->color, 3.0f);
	al_draw_line(-6, 4, -1, 4, ship->color, 3.0f);
	al_draw_line(6, 4, 1, 4, ship->color, 3.0f);
	return;
}


void destroy_ship(Spaceship* s) {
	free(s);
}

void rotate_ship(Spaceship* s, ALLEGRO_EVENT * event) {
	if (event->keyboard.keycode == ALLEGRO_KEY_LEFT) {
		
		//s->sx = s->sx + 20.0f;
		s->heading -= ROTATE_DELTA;
		
	}
	else if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
		s->heading += ROTATE_DELTA;
	}

}
//key event space bar
void ship_accelerate(Spaceship* s) 
{
	if (s->speed < MAX_SPEED) {

		s->speed += ACCELERATE_SHIP;
	}
	 if (s->speed > MAX_SPEED){
		
		s->speed = MAX_SPEED;
		
	}
	 return;

}

//key event back
void ship_decelerate(Spaceship* s) {
	if (s->speed > 0) {
		s->speed -= DECELERATE_SHIP;
	}
	else if (s->speed < 0) {
		s->speed = 0;
	}
	return;
	
}

void ship_position(Spaceship* s) {
	//calculate the geometrical changes
	float dx = sin(s->heading) * (s->speed);
	float dy = -cos(s->heading) * (s->speed);


	//change positions

	s->sx += dx;
	s->sy += dy;

	

	update_ship_location(&s->sx, &s->sy);
	return;
}
//call to update the location of the ship
void update_ship_location(float *x, float *y) {
		if (*x > (float)SCREEN_WIDTH)
			* x = 0;
		if (*x < 0)
			* x = (float)SCREEN_WIDTH;
		if (*y > (float) SCREEN_HEIGHT)
			* y = 0;
		if (*y < 0)
			* y = (float)SCREEN_HEIGHT;

		return;
	
}


