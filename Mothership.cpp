#include "Mothership.h"
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <stdio.h>
#include <string>
Mothership::Mothership(int x, int y, ALLEGRO_BITMAP* img) {
	xPos = x;
	yPos = y;
	health = 100;
	image = img;
	xDir = 2;
	yDir = 0;
}

void Mothership::draw() {
	if (health < 0) health = 0;
	al_draw_text(font, al_map_rgb(255, 255, 255), 400, 50, NULL, "Enemy Health");
	al_draw_filled_rectangle(400, 20, 400 + health, 40, al_map_rgb(255, 0, 0));
	al_draw_rectangle(400, 20, 500, 40, al_map_rgb(0, 150, 0), 3);
	al_draw_bitmap(image, xPos, yPos, NULL);
}

void Mothership::move() {
	if (xPos >= 900 || xPos <= 0)
		xDir *= -1;

	xPos += xDir;
	yPos += yDir;
}

void Mothership::decreaseHealth() {
	health--;
}

int Mothership::getX() {
	return xPos;
}

int Mothership::getY() {
	return yPos;
}

int Mothership::getHealth() {
	return health;
}