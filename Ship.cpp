#include "Ship.h"
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
Ship::Ship(int x, int y, ALLEGRO_BITMAP* image) {
	xPos = x;
	yPos = y;
	shipPic = image;
	alive = true;
	cellNum = 0;
	health = 100;
	dir = 0;
}

void Ship::draw() {
	if (health < 0) health = 0;
	al_draw_text(font1, al_map_rgb(255, 255, 255), 20, 50, NULL, "Player Health");
	al_draw_filled_rectangle(20, 20, 20 + health, 40, al_map_rgb(0, 0, 255));
	al_draw_rectangle(20, 20, 120, 40, al_map_rgb(0, 150, 0), 3);
	al_draw_bitmap_region(shipPic, (cellNum * 32), 0, 32, 32, xPos, yPos, (dir == 2) ? ALLEGRO_FLIP_HORIZONTAL : NULL);
}

double Ship::getX() {
	return xPos;
}
double Ship::getY() {
	return yPos;
}
void Ship::setX(double x) {
	xPos = x;
}
void Ship::setY(double y) {
	yPos = y;
}
int Ship::getcellNum() {
	return cellNum;
}
void Ship::setcellNum(int newcellNum) {
	cellNum = newcellNum;
}
int Ship::getDir() {
	return dir;
}
void Ship::setDir(int newDir) {
	dir = newDir;
}
int Ship::getHealth() {
	return health;
}

void Ship::decreaseHealth() {
	health--;
}