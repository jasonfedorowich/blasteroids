#include "logic.h"

//TODO fix this function to take Blasts as a parameter
void is_collision(Asteroid* a)
{      
	Blast** blasts = get_blasts();
	
	for (int i = 0; i < current_blast; i++) {
		Blast* blast = blasts[i];
		if (blast_radius(blast, a)) {
			a->gone = 0;
			return;
		}
	}

	return;
}

 void adjust_array(int pos, void*** array, int* size) {
	for (int i = pos; i < *size; i++) {

		array[i] = array[i + 1];
		array[i + 1] = NULL;

	}
	(*size)--;
}
 
 int blast_radius(Blast* b, Asteroid* a) {
	 if (binary_search_integer(b->sx, a->sx) && binary_search_integer(b->sy, a->sy))
		 return 1;
	 return 0;
 }

 int binary_search_integer(int i, int query) {
	 int first, last, middle;
	 first = i - 10;
	 last = i + 10;	 

	 while (first <= last) {
		 middle = (first + last) / 2;
		 if (query > i)
			 first = middle + 1;
		 else if (query < i) 
			 last = middle - 1;
		 else
			 return middle;	 
		 }
		 return -1;
	 
 }

