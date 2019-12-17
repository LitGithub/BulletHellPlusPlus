#pragma once
class star {
private:
	int xPos;
	int yPos;
	int size;
	int r;
	int g;
	int b;
public:
	star(int red, int green, int blue);
	void draw();
	void move();
	void reposition(int red, int green, int blue);
};