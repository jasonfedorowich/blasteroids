#pragma once
typedef struct vector {
	void** items;
	int capacity;
	int total;
} vector;

vector* vector_init(int capacity);
int vector_total(vector*);
static void vector_resize(vector*, int);
void vector_add(vector*, void*);
void vector_set(vector*, int, void*);
void* vector_get(vector*, int);
void vector_delete(vector*, int);
void vector_free(vector*);
