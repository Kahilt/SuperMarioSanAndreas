#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
using namespace std;
#define length 1366
#define width 770

 int main(){

	 al_init();

	 bool done = false, draw = false;
	 int x = 10, y = 700, movespeed = 5;
	 int state = NULL;
	 const float FPS = 60.0;
	 enum Direction {/*UP, DOWN, */LEFT, RIGHT};
	 ALLEGRO_COLOR blue = al_map_rgb(44, 117, 255);
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
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	

	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("bg.png");
	ALLEGRO_BITMAP *imagewindowsky = al_load_bitmap("Sky.png");
	ALLEGRO_BITMAP *imagecar = al_load_bitmap("mcar.png");
	ALLEGRO_BITMAP *imagecopcar = al_load_bitmap("ccar.png");

	al_start_timer(timer);

	while (!done)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		if (events.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
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
			/*else */if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				x -= movespeed;
			else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				x += movespeed;
			draw = true;
		}

		if (draw)
		{
			draw = false;
			//al_draw_rectangle(x, y, x + 20, y + 20, blue, 2.0);
			al_flip_display();
			al_draw_bitmap(imagewindowsky,/* 1*/x, 2, NULL);
			al_draw_bitmap(imagewindow,/* 1*/x, 5, NULL);
			al_draw_bitmap(imagecar, 175+x, 553, NULL);
			al_draw_bitmap(imagecopcar, 700+x, 635, NULL);
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
	return 0;
}