#include <allegro5/allegro.h>
#include<allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <iostream>
#include <vector>
#include "Ship.h"
#include "Missile.h"
#include "Star.h"
#include "Mothership.h"
#include "Bullets.h"
using namespace std;
enum MYKEYS { KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE };
int stage = 0;
int red = 255;
int green = 0;
int blue = 0;

void rainbow();
int main() {
	al_init();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//set up game screen, event queue, and timer
	ALLEGRO_DISPLAY* display = al_create_display(1000, 1000);
	ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
	ALLEGRO_BITMAP* dinopic = al_load_bitmap("dinopic.png");
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 100);
	al_start_timer(timer);
	//bitmap

	al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

	//start dark for a second
	for (float i = 0; i < 1; i += .0005) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}
	//fade in
	for (float i = 0; i < 1; i += .0008) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, i), 50, 50, 0);
		al_flip_display();
	}
	//stay solid for a second
	for (float i = 0; i < 1; i += .001) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(1, 1, 1, 1), 50, 50, 0);
		al_flip_display();
	}
	//fade out
	for (float i = 1; i > 0; i -= .0005) {
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_tinted_bitmap(dinopic, al_map_rgba_f(i, 1, 1, i), 50, 50, 0);
		al_flip_display();
	}
	al_rest(5);

	al_destroy_bitmap(dinopic);


	//game variables
	bool key[5] = { false, false, false, false, false }; //holds key clicks
	bool redraw = true; //variable needed for render section
	bool doexit = false; //handles game loop

	//tell event queue what to look for
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//define ship
	Ship player(500, 800, al_load_bitmap("ship.png"));
	Mothership Enemy1(400, 200, al_load_bitmap("mothership.png"));
	int ticker = 0;

	vector<Missile*> missiles;
	vector<Missile*>::iterator iter2;
	for (int i = 0; i < 100; i++) {
		Missile* newMissile = new Missile(0, 0, al_load_bitmap("missile.png"));
		missiles.push_back(newMissile);
	}

	vector<star*> starfield;
	vector<star*>::iterator iter3;
	for (int i = 0; i <= 100; i++) {
		star* newStar = new star(red, green, blue);
		starfield.push_back(newStar);
	}

	vector<Bullet*> bullets;
	vector<Bullet*>::iterator iter4;

	int AlienHit = 0;
	int HitX = 0;
	int HitY = 0;
	int justShot = 0;
	int counter = 0;
	float minBullets = 10;
	while (!doexit) { //game loop!
		ALLEGRO_EVENT ev;

		al_wait_for_event(event_queue, &ev);

		//timer (physics) section////////////////////////////////////////
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			rainbow();
			counter++;
			minBullets -= .0001;
			if (counter > minBullets) {
				bullets.push_back(new Bullet(Enemy1.getX() + 63, Enemy1.getY() + 31));
				counter = 0;
			}
			int cellNum = player.getcellNum();
			int dir = player.getDir();
			ticker++;
			if (ticker > 10) {
				ticker = 0;
			}

			if (ticker == 0) {
				cellNum++;
			}

			if (dir == KEY_UP || dir == KEY_DOWN) {
				if (cellNum > 4)
					cellNum = 0;
			}
			if (dir == KEY_LEFT || dir == KEY_RIGHT) {
				if (cellNum < 5)
					cellNum = 5;
				if (cellNum > 9)
					cellNum = 5;
			}
			player.setcellNum(cellNum);
			int xPos = player.getX();
			int yPos = player.getY();
			//move player 4 pixels in a direction when key is pressed
			if (key[KEY_UP] && yPos >= 0) {
				yPos -= 4.0;
			}
			if (key[KEY_DOWN] && yPos <= 968) {
				yPos += 4.0;
			}
			if (key[KEY_LEFT] && xPos >= 0) {
				xPos -= 4.0;
			}
			if (key[KEY_RIGHT] && xPos <= 968) {
				xPos += 4.0;
			}
			if (key[KEY_SPACE]) {
				for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
					if ((*iter2)->isalive() == false && justShot > 5) {
						(*iter2)->shoot(xPos, yPos);
						justShot = 0;
					}
				}
			}
			Enemy1.move();
			player.setX(xPos);
			player.setY(yPos);
			justShot++;
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				if ((*iter2)->isalive()) {
					(*iter2)->move();
				}
				if ((*iter2)->collide((Enemy1.getX() + 63), Enemy1.getY() + 31)) {
					AlienHit = 30;
					HitX = (*iter2)->getX();
					HitY = (*iter2)->getY();
					Enemy1.decreaseHealth();
					(*iter2)->kill();
				}
				if ((*iter2)->offScreen()) {
					(*iter2)->kill();
				}
			}
			for (iter4 = bullets.begin(); iter4 != bullets.end(); iter4++) {
				if ((*iter4)->collide((player.getX() + 16), player.getY() + 16) &&!(*iter4)->shouldDelete) {
					player.decreaseHealth();
					(*iter4)->shouldDelete = true;
				}
				if ((*iter4)->offScreen() && !(*iter4)->shouldDelete) {
					(*iter4)->shouldDelete = true;
				}
				if ((*iter4)->isalive() && !(*iter4)->shouldDelete)
					(*iter4)->move();
				if ((*iter4)->shouldDelete) {
					(*iter4)->~Bullet();
					iter4 = bullets.erase(iter4);
				}
			}
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->reposition(red, green, blue);
				(*iter3)->move();
			}
			redraw = true;
		}
		//keyboard and screen sections//////////////////////////////////////////
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = true;
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false;
				break;
			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;
			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;
			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			case ALLEGRO_KEY_SPACE:
				key[KEY_SPACE] = false;
				break;
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
		}
		//render section//////////////////////////////////////////////////
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0)); //wipe screen black between drawing (without this things smear)
			for (iter2 = missiles.begin(); iter2 != missiles.end(); iter2++) {
				(*iter2)->draw(red, green, blue);
			}
			for (iter3 = starfield.begin(); iter3 != starfield.end(); iter3++) {
				(*iter3)->draw();
			}
			cout << "flag1" << endl;
			for (iter4 = bullets.begin(); iter4 != bullets.end(); iter4++) {
				if(!(*iter4)->shouldDelete)
				(*iter4)->draw(red, green, blue);
			}
			cout << "flag2" << endl;

			player.draw();
			if (AlienHit > 0) {
				al_draw_filled_circle(HitX, HitY, 10, al_map_rgb(red, green, blue));
				AlienHit--;
			}
			Enemy1.draw();
			al_flip_display(); //flip everything from memory to gamescreen
		}//end render

	}//end game loop
	//clean up memory
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	return 0;
}


void rainbow() {
	switch (stage) {
	case 0: // blue up
		blue++;
		if (blue >= 255)
			stage++;
		break;
	case 1: // red down
		red--;
		if (red == 0)
			stage++;
		break;
	case 2: // green up
		green++;
		if (green >= 255)
			stage++;
		break;
	case 3: // blue down
		blue--;
		if (blue == 0)
			stage++;
		break;
	case 4: // red up
		red++;
		if (red >= 255)
			stage++;
		break; // green removal
	case 5:
		green--;
		if (green == 0)
			stage++;
		break;
	case 6: // blue and green increase
		if (blue != 255)
			blue++;
		if (green != 255)
			green++;
		if (red == 255 && blue == 255 && green == 255)
			stage++;
		break;
	case 7: // rgb decrease
		if (red != 0)
			red--;
		if (green != 0)
			green--;
		if (blue != 0)
			blue--;
		if (red <= 0 && blue <= 0 && green <= 0)
			stage++;
		break;
	case 8: // red increase to reset
		red++;
		if (red == 255)
			stage = 0;
		break;

	}
	//cout << "RGB: " << red << ", " << green << ", " << blue << endl;
};

