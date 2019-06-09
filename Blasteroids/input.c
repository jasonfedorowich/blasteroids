#include "input.h"
#include "spaceship.h";
#include "blast.h"

void handle_user_input(Spaceship* s, ALLEGRO_EVENT* event)
{
	if (event->keyboard.keycode == ALLEGRO_KEY_LEFT || event->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
		rotate_ship(s, event);
	}
	else if (event->keyboard.keycode == ALLEGRO_KEY_UP) {
		ship_accelerate(s);
	}
	else if (event->keyboard.keycode == ALLEGRO_KEY_SPACE) {
		ship_blast(s);

	}
	else if (event->keyboard.keycode == ALLEGRO_KEY_DOWN) {
		ship_decelerate(s);
	}
	return;
}


