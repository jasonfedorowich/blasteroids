#include "logic.h"

void is_collision(Asteroid* a)
{
	Blast** blasts = get_blasts();
	
	for (int i = 0; i < current_blast; i++) {
		Blast* blast = blasts[i];
		if (blast->sx == a->sx && blast->sy == a->sy) {
			a->gone = 0;
			return;
		}
	}

	return;
}
