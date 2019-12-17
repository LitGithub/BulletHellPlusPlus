#pragma once

class Ship {
private:
	double xPos;
	double yPos;
	int justShot;
	int cellNum;
public:
	Ship(int x, int y);
	void draw();
	void move();
	double getX();
	double getY();
	void setX();
	void setY();
};