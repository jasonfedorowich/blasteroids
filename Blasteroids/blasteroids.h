#pragma once
#define FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



void update();

static double random_double_number(double min, double max) {
	return (double)(rand() % (int)(max + 1 - min)) + min;
}
//TODO fix random number generator
static int random_number(int min, int max) {
	return (rand() % (max + 1 - min)) + min;

}
