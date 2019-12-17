#pragma once
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>

class Bullet {
private:
	double xPos;
	double yPos;
	double angle;
	double radius;
	bool isAlive = false;
public:
	bool shouldDelete = false;
	Bullet(int x, int y);
	void move();
	void draw(int red, int green, int blue);
	void kill();
	int getX();
	int getY();
	bool isalive();
	bool offScreen();
	void shoot(int x, int y);
	bool collide(double x, double y);
};
