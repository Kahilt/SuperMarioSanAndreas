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
	 const float EFPS = 13.0;
	 enum Direction {/*UP, DOWN, */LEFT, RIGHT};
	 
	// int dir = DOWN;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE);
	display = al_create_display(length, width);
	al_set_window_position(display, 200, 100);

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
	
	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("bgc.png");
	ALLEGRO_BITMAP *imagewindowsky = al_load_bitmap("sky1.png");
	ALLEGRO_BITMAP *imagecar = al_load_bitmap("mcar.png");
	ALLEGRO_BITMAP *imagecopcar = al_load_bitmap("ccar.png");
	ALLEGRO_BITMAP *mario = al_load_bitmap("Mario_Nintendo.png");
	ALLEGRO_TRANSFORM CAMERA;
	
	Enemies gangster;						//creates 1 object of enemies class
	gangster.x = 1000;						//x position of enemy
	gangster.startX = 1000;					//starting postion of enemy
	gangster.y = 570;
	gangster.endX = 1500;					//ending postion of enemy

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


	ALLEGRO_BITMAP *punch_ganster_right = al_load_bitmap("Punching_gangster_RIGHT.png");
	ALLEGRO_BITMAP *punch_ganster_left = al_load_bitmap("Punching_gangster_LEFT.png");

	ALLEGRO_BITMAP *smallPillar = al_load_bitmap("Single_pillar_small.png");
	ALLEGRO_BITMAP *medPillar = al_load_bitmap("Single_pillar_medium.png");
	ALLEGRO_BITMAP *largePillar = al_load_bitmap("Single_pillar_large.png");
	
	al_start_timer(timer);
	al_start_timer(enemyTimer);

	while (!done)
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

			gangster.move(movespeed);

		}

		if (draw)
		{
			draw = false;
			
			al_flip_display();//shows the display window on pc window
//			al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);
			for (int i = 0; i <= 5; i++)//for loop created to redraw the background according to level lenght
			{
					al_draw_bitmap(imagewindowsky,(length*i), 2, NULL);	// draws sky to window
					al_draw_bitmap(imagewindow,(length*i), 5, NULL);	// draws buildings to window
				}
			al_draw_bitmap(mario, x, y,NULL);
			
			pillar1.draw(smallPillar, medPillar, largePillar);
			pillar2.draw(smallPillar, medPillar, largePillar);
			pillar3.draw(smallPillar, medPillar, largePillar);
			gangster.draw(punch_ganster_right, punch_ganster_left, (events.timer.source == enemyTimer));
		}

		
	}
	

	
	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	
	//al_flip_display();
	//al_rest(10);
	//al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_bitmap(imagewindow);
	al_destroy_bitmap(imagewindowsky); 
	al_destroy_bitmap(imagecar);
	al_destroy_bitmap(imagecopcar);
	al_destroy_timer(timer);

	al_destroy_bitmap(punch_ganster_right);
	al_destroy_bitmap(punch_ganster_left);
	return 0;
}