#include "Star.h"
#include <allegro5/allegro.h>
#include <allegro5\allegro_primitives.h>

star::star(int red, int green, int blue) {
	xPos = rand() % 1000;
	yPos = rand() % 1000;
	r = red;
	g = green;
	b = blue;
	size = rand() % 5;
}

void star::draw() {
	al_draw_filled_circle(xPos, yPos, size, al_map_rgb(r, g, b));
}

void star::reposition(int red, int green, int blue) {
	if (yPos >= 1000) {
		r = red;
		g = green;
		b = blue;
		size = rand() % 5;
		xPos = rand() % 1000;
		yPos = 0;
	}
}

void star::move() {
	yPos += 5;
}