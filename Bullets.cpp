#include"Bullets.h"
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <iostream>
using namespace std;
Bullet::Bullet(int x, int y) {
	xPos = x;
	yPos = y;
	radius = 10;
	angle = 0;
	isAlive = true;
	shouldDelete = false;
}
void Bullet::move() {
	switch (rand() % 4 + 1) {
	case 1:
		angle += .1;
		xPos = xPos + cos(angle);
		yPos++;
		break;
	case 2:
		angle -= .1;
		xPos = xPos + cos(angle);
		yPos++;
		break;
	case 3:
		angle += .5;
		xPos = xPos + cos(angle);
		yPos++;
		break;
	case 4:
		angle -= .5;
		xPos = xPos + cos(angle);
		yPos++;
		break;
	}
}
void Bullet::draw(int red, int green, int blue) {
	if (isAlive) {
		al_draw_filled_circle(xPos, yPos, 5, al_map_rgb(red, green, blue));
	}
}
void Bullet::kill() {
	isAlive = false;
	xPos = 0;
	yPos = 0;
}
int Bullet::getX() {
	return xPos;
}
int Bullet::getY() {
	return yPos;
}
bool Bullet::offScreen() {
	if (yPos > 1000) return true;
	else return false;

}
bool Bullet::isalive() {
	return isAlive;
}
void Bullet::shoot(int x, int y) {
	isAlive = true;
	xPos = x;
	yPos = y;
}
bool Bullet::collide(double x, double y) {
	double dx = (xPos - x) * (xPos - x);
	double dy = (yPos - y) * (yPos - y);

	double dxy = sqrt(dx + dy);

	if (dxy <= 32) {
		//cout << dxy << endl;
		return true;
	}
	else return false;
}