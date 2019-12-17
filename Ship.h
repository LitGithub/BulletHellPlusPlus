#pragma once
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
class Ship {
private:
	double xPos;
	double yPos;
	ALLEGRO_BITMAP *shipPic;
	int cellNum;
	bool alive;
	int dir;
	int health;
	ALLEGRO_FONT* font1 = al_load_ttf_font("Minecraft.ttf", 20, NULL);
public:
	Ship(int x, int y, ALLEGRO_BITMAP *image);
	void draw();
	double getX();
	double getY();
	int getcellNum();
	void setcellNum(int newcellNum);
	void setX(double x);
	void setY(double y);
	int getDir();
	int getHealth();
	void decreaseHealth();
	void setDir(int newDir);
};