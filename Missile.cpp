#include"Missile.h"
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <iostream>
using namespace std;
Missile::Missile(int x, int y, ALLEGRO_BITMAP *image) {
	xPos = x;
	yPos = y;
	rocket = image;
	radius = 10;
	angle = 0;
}
void Missile::move() {
	yPos -= 5;
}
void Missile::draw(int red, int green, int blue) {
	if (isAlive) {
		al_draw_tinted_bitmap(rocket,al_map_rgb(red, green, blue), xPos, yPos, NULL);
	}
}
void Missile::kill() {
	isAlive = false;
	xPos = 0;
	yPos = 0;
}
int Missile::getX() {
	return xPos;
}
int Missile::getY() {
	return yPos;
}
bool Missile::offScreen() {
	if (yPos < 0) return true;
	else return false;

}
bool Missile::isalive() {
	return isAlive;
}
void Missile::shoot(int x, int y) {
	isAlive = true;
	xPos = x;
	yPos = y;
}
bool Missile::collide(double x, double y) {
	double dx = (xPos - x) * (xPos - x);
	double dy = (yPos - y) * (yPos - y);

	double dxy = sqrt(dx + dy);
	
	if (dxy <= 50) {
		//cout << dxy << endl;
		return true;
	}
	else return false;
}