#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
using namespace std;
#define length 1366 //defining the screen lenght 
#define width 770  //defining the screen width 
#include "Enemies.cpp"
#include "pilars.cpp"
#include "Cars.cpp"

void cameraUpdate(float *camerposition, float x, float y, int w, int h){
	camerposition[0] = -(length / 2) + (x + w / 2);				//positioning the camera at midpoint of the screen on the x axis
	if (camerposition[0] < 0)									//check if the position is less then zero and if true then make it equal to zero
		camerposition[0] = 0;
}

 int main(){//main function

	 al_init();


	 bool done = false, draw = false;
	 int x = 0, y = 0, movespeed = 5;
	 int state = NULL;
	 const float FPS = 60.0;
	 const float EFPS = 15.0;
	 enum Direction {/*UP, DOWN, */LEFT, RIGHT};
	 int level = 1;
	 const int numOfEnemys = 4;					//contains the number of enemies
	 const int numCars = 8;
	 
	// int dir = DOWN;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE);
	display = al_create_display(length, width);
	al_set_window_position(display, 0, 0);

	al_init_image_addon();

	al_init_primitives_addon();
	al_install_keyboard();
	float cameraposition[2] = { 0, 0 };

	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *enemyTimer = al_create_timer(1.0 / EFPS);			//controls the animation of enemies  
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(enemyTimer));
	ALLEGRO_TRANSFORM CAMERA;

	///////////////////////////////////////////////////////////////////////IMAGE LOADING/////////////////////////////////////////////////////////////


	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("bgc.png");
	ALLEGRO_BITMAP *imagewindowsky = al_load_bitmap("sky1.png");
	ALLEGRO_BITMAP *imagecar = al_load_bitmap("mcar.png");
	ALLEGRO_BITMAP *imagecopcar = al_load_bitmap("ccar.png");
	ALLEGRO_BITMAP *mario = al_load_bitmap("Mario_Nintendo.png");
	ALLEGRO_BITMAP *punch_gangster = al_load_bitmap("Punching_gangster.png");
	ALLEGRO_BITMAP *chain_gangster = al_load_bitmap("Chain_gangster.png");
	
	ALLEGRO_BITMAP *smallPillar = al_load_bitmap("Single_pillar_small.png");
	ALLEGRO_BITMAP *medPillar = al_load_bitmap("Single_pillar_medium.png");
	ALLEGRO_BITMAP *largePillar = al_load_bitmap("Single_pillar_large.png");
	
	///////////////////////////////////////////////////CALLING CLASSES/////////////////////////////////////////////////////////////////////////////

	Enemies gangster[numOfEnemys];						//creates 1 object of enemies class
	gangster[0].setValues(1000, 570, 1000, 1500,1);	//sets values to enemy
	gangster[1].setValues(2016, 590, 2016, 2200,1);
	gangster[2].setValues(4000, 600, 4000, 4500,2);
	gangster[3].setValues(3000, 600, 3000, 3800, 2);

	pilars pillar1;
	pillar1.x = 500;
	pillar1.y = 570;
	pillar1.size = 1;

	pilars pillar2;
	pillar2.x = 586;
	pillar2.y = 516;
	pillar2.size = 2;


	pilars pillar3;
	pillar3.x = 672;
	pillar3.y = 396;
	pillar3.size = 3;

	Cars  car[numCars];//object of Cars class
	car[1].setCars(2500, 650, 1);
	car[2].setCars(3600, 650, 1);
	car[3].setCars(1300, 650, 1);
	car[3].setCars(1500, 650, 1);
	car[4].setCars(300, 660, 2);
	car[5].setCars(4700, 660, 2);
	car[6].setCars(7800, 660, 2);
	car[7].setCars(7000, 660, 2);
	
	////////////////////////////////////////////GAME START//////////////////////////////////////////////////////////////////////////////////////////////
	al_start_timer(timer);	// main timer
	al_start_timer(enemyTimer);	// enemy timer

	while (!done)	// main game loop
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:	// closes window if escape key is pressed
				done = true;
			}
		}

		if (events.type == ALLEGRO_EVENT_TIMER)
		{
			al_get_keyboard_state(&keyState);
			if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
				y += movespeed;
			else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
				y -= movespeed;
			else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				x += movespeed;	// moves background to the left to creat the illusion of the player moving through the game world
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				x -= movespeed;	// moves background to the right to creat the illusion of the player moving through the game world

			}
			draw = true;
			cameraUpdate(cameraposition, x, y, length / 2, width / 2);//updates the position of camera as mario moves
			al_identity_transform(&CAMERA);                           //transforms the image
			al_translate_transform(&CAMERA, -cameraposition[0], -cameraposition[1]);//translates the camera position
			al_use_transform(&CAMERA);

			for (int i = 0; i < numOfEnemys; i++)
			{
				gangster[i].move(movespeed / 2);
			}

		}

		if (draw)
		{
			draw = false;

			al_flip_display();//shows the display window on pc window
			//			al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);
			for (int i = 0; i <= 5; i++)//for loop created to redraw the background according to level lenght
			{
				al_draw_bitmap(imagewindowsky, (length*i), 0, NULL);	// draws sky to window
				al_draw_bitmap(imagewindow, (length*i), 3, NULL);	// draws buildings to window.
			}
			al_draw_bitmap(mario, x, y, NULL);

			//////////////////////////LEVEL 1//////////////////////////////////////////////////////////////////

			if (level == 1)
			{
				pillar1.draw(smallPillar, medPillar, largePillar);
				pillar2.draw(smallPillar, medPillar, largePillar);
				pillar3.draw(smallPillar, medPillar, largePillar);

				for (int i = 0; i < numCars; i++)
				{
					car[i].draw(imagecar, imagecopcar);	// calling draw method from Cars class
				}

				for (int i = 0; i < numOfEnemys; i++)
				{
					gangster[i].draw(punch_gangster, chain_gangster,(events.timer.source == enemyTimer));	// draw method from Enemies class
				}
			}
		}

		
	}
	

	
	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	
	//al_flip_display();
	
	//al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_bitmap(imagewindow);
	al_destroy_bitmap(imagewindowsky); 
	al_destroy_bitmap(imagecar);
	al_destroy_bitmap(imagecopcar);
	al_destroy_timer(timer);

	al_destroy_bitmap(punch_gangster);
	al_destroy_bitmap(chain_gangster);
	
	return 0;
}