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



 int main(){//main function

	 al_init();


	 bool done = false, draw = false;
	 int x = 0, y = 0, movespeed = 5;
	 int state = NULL;
	 const float FPS = 60.0;
	 const float EFPS = 15.0;
	 enum Direction {/*UP, DOWN, */LEFT, RIGHT};
	 
	// int dir = DOWN;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(length, width);
	al_set_window_position(display, 200, 100);

	al_init_image_addon();

	al_init_primitives_addon();
	al_install_keyboard();

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
	
	Enemies gangster;						//creates 1 object of enemies class
	gangster.x = 1000;						//x position of enemy
	gangster.startX = 1000;					//starting postion of enemy
	gangster.y = 570;
	gangster.endX = 1500;					//ending postion of enemy

	ALLEGRO_BITMAP *punch_ganster_right = al_load_bitmap("Punching_gangster_RIGHT.png");
	ALLEGRO_BITMAP *punch_ganster_left = al_load_bitmap("Punching_gangster_LEFT.png");

	
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
			//if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
				//y += movespeed;
			//else if (al_key_down(&keyState, ALLEGRO_KEY_UP))
				//y -= movespeed;
			/*else */
			if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			{
				x -= movespeed;	// moves background to the left to creat the illusion of the player moving through the game world
				gangster.updateX(-1*movespeed);
			}
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
			{
				x += movespeed;	// moves background to the right to creat the illusion of the player moving through the game world
				gangster.updateX(movespeed);
			}
			draw = true;

			gangster.move(movespeed);

		}

		if (draw)
		{
			draw = false;
			
			al_flip_display();//shows the display window on pc window
//			al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);
			for (int i = 0; i <= 5; i++)//for loop created to redraw the background according to level lenght
			{
				if (x <= 0){
					al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);	// draws sky to window
					al_draw_bitmap(imagewindow,/* 1*/x + (length*i), 5, NULL);	// draws buildings to window
				}
			}
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