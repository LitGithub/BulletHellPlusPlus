#pragma once
#include <allegro5/allegro.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
class Mothership {
private:
	int xPos;
	int yPos;
	int xDir;
	int yDir;
	int health;
	ALLEGRO_BITMAP* image;
	ALLEGRO_FONT* font = al_load_ttf_font("Minecraft.ttf", 20, NULL);
public:
	Mothership(int x, int y, ALLEGRO_BITMAP* img);
	void draw();
	void move();
	void decreaseHealth();
	int getX();
	int getY();
	int getHealth();	
};