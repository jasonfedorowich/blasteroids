#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"
#include "blasteroids.h"
#include "input.h"
#include "blast.h"
static Spaceship* s = NULL;
ALLEGRO_EVENT_QUEUE* queue = NULL;
ALLEGRO_TIMER* timer = NULL;
ALLEGRO_DISPLAY* disp = NULL;
ALLEGRO_FONT* font = NULL;


bool get_user_input(ALLEGRO_EVENT* event) {
	switch (event->keyboard.keycode) {
	case ALLEGRO_KEY_LEFT:
		break;
	case ALLEGRO_KEY_UP:
		break;
	}
}

void handle_event(ALLEGRO_EVENT* event) {

}
void must_init(bool test, const char* description)
{
	if (test) return;

	printf("couldn't initialize %s\n", description);
	exit(1);
}

void init_game()
{
	must_init(al_init(), "allegro");
	must_init(al_install_keyboard(), "keyboard");

	 timer = al_create_timer(1.0 / 30.0);
	must_init(timer, "timer");

	queue = al_create_event_queue();
	must_init(queue, "queue");

	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
	al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

	disp = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
	must_init(disp, "display");
	 font = al_create_builtin_font();
	must_init(font, "font");



	must_init(al_init_primitives_addon(), "primitives");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(disp));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	s = createship();
	s->sx = SCREEN_WIDTH / 2;
	s->sy = SCREEN_HEIGHT / 2;
	
}




void update()
{
	ship_position(s);
	draw_spaceship(s);
	
	//TODO put in thread to manage the blasts
	calculate_all_blast_positions();
	draw_all_blasts();


	al_flip_display();
}

int main()
{

	init_game();
	bool done = false;
	bool redraw = true;
	ALLEGRO_EVENT event;


	al_start_timer(timer);

	bool isRunning = true;
	double old_time = al_get_time();

	while (isRunning) {
		ALLEGRO_EVENT event;

 		al_wait_for_event(queue, &event);

		if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP)
		{
			//handle_event(&event);
			//rotate_ship(s, &event);
			handle_user_input(s, &event);

			redraw = true;


		}

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			isRunning = false;



		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;

		}

		if (redraw && al_is_event_queue_empty(queue)) {
			al_clear_to_color(al_map_rgb(0, 0, 0));

			update();
		}
	}

	al_destroy_font(font);
	al_destroy_display(disp);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);
	destroy_ship(s);

	return 0;
}