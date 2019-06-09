#pragma once
#define FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



void update();

static double random_double_number(double min, double max) {
	return (double)(rand() % (int)(max - min + 1) + min);
}

static int random_number(int min, int max) {
	return (rand() % (max - min + 1)) + min;

}
