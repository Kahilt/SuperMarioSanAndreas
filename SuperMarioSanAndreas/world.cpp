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
#include "world obstacles.cpp"

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
	 const int numOfEnemys = 7;					//contains the number of enemies
	 
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
	ALLEGRO_BITMAP *imagebus = al_load_bitmap("bus.png");
	
	ALLEGRO_BITMAP *smallPillar = al_load_bitmap("brick_grey.png");
	ALLEGRO_BITMAP *medPillar = al_load_bitmap("download.png");
	
	///////////////////////////////////////////////////CALLING CLASSES/////////////////////////////////////////////////////////////////////////////

	Enemies gangster[numOfEnemys];						//creates 1 object of enemies class
	gangster[0].setValues(1000, 590, 1000, 1500,1);	//sets values to enemy
	gangster[1].setValues(1800, 590, 1800, 2200,1);
	gangster[2].setValues(3000, 600, 3000, 3800,2);
	gangster[3].setValues(4050, 600, 4050, 4800, 2);
	gangster[4].setValues(6500, 590, 5500, 5900, 1);
	gangster[5].setValues(6500, 590, 5900, 6700, 1);
	gangster[6].setValues(6500, 600, 7600, 8000, 2);
   
	///////////////////////setting values for the position of cars//////////////////////////////////////////
	Cars car[6];	//car1, car2, car3, car4, car5, car6, car7, car8, car9, car10, car11, car12;
	
	worldObstacles *obstacle[6];
	for (int i = 0; i < 6; i++)
	{
		obstacle[i] = &car[i];
	}
	/*
	worldObstacles *obstacle1 = &car1;
	worldObstacles *obstacle2 = &car2;
	worldObstacles *obstacle3 = &car3;
	worldObstacles *obstacle4 = &car4;
	worldObstacles *obstacle5 = &car5;
	worldObstacles *obstacle6 = &car6;*/

	obstacle[0]->setvalue(2500, 650, 1);
	obstacle[1]->setvalue(3600, 650, 1);
	obstacle[2]->setvalue(1300, 650, 1);
	obstacle[3]->setvalue(850, 660, 2);
	obstacle[4]->setvalue(4700, 660, 2);
	obstacle[5]->setvalue(7000, 590, 3);
	
	///////////////////////////////////////setting positions of pillars(brikes)////////////////////////////////////////////////
   /* pilars pillar1, pillar2, pillar3, pillar4, pillar5, pillar6;
	worldObstacles *obstacle7 = &pillar1;
	worldObstacles *obstacle8 = &pillar2;
	worldObstacles *obstacle9 = &pillar3;
	worldObstacles *obstacle10 = &pillar4;
	worldObstacles *obstacle11 = &pillar5;
	worldObstacles *obstacle12 = &pillar6;
	obstacle7->setvalue(2500, 500, 1);
	obstacle8->setvalue(3600, 500, 1);
	obstacle9->setvalue(1300, 500, 1);
	obstacle10->setvalue(300, 500, 2);
	obstacle11->setvalue(4700,500, 2);
	obstacle12->setvalue(7000,500, 2);*/

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
				obstacle[0]->draw(imagecar, imagecopcar, imagebus);
				obstacle[1]->draw(imagecar, imagecopcar, imagebus);
				obstacle[2]->draw(imagecar, imagecopcar, imagebus);
				obstacle[3]->draw(imagecar, imagecopcar, imagebus);
				obstacle[4]->draw(imagecar, imagecopcar, imagebus);
				obstacle[5]->draw(imagecar, imagecopcar, imagebus);
			/*obstacle7->draw(smallPillar, medPillar);
				obstacle8->draw(smallPillar, medPillar);
				obstacle9->draw(smallPillar, medPillar);
				obstacle10->draw(smallPillar, medPillar);
				obstacle11->draw(smallPillar, medPillar);
				obstacle12->draw(smallPillar, medPillar);
				*/
				
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
	al_destroy_bitmap(smallPillar);
	al_destroy_bitmap(medPillar);
	al_destroy_bitmap(punch_gangster);
	al_destroy_bitmap(chain_gangster);
	
	return 0;
}