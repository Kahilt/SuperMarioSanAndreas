#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


using namespace std;
//creating variables to be used
const int width = 1366;
const int height = 770;
int imageWidth = 0;
int imageHeight = 0;

bool keys[] = { false, false, false };
enum KEYS{ ENTER, ESCAPE, SPACE};

enum PAGE{ MENU, PLAYING, PAUSE, GAMEOVER };
 
int splash(int argc, char **argv)
{
	bool done = false;
	bool render = false;
	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	int page = MENU;

	//creating allegro variables
	ALLEGRO_DISPLAY *display= NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *start = NULL;
	ALLEGRO_BITMAP *pause = NULL;
	ALLEGRO_BITMAP *gameover = NULL;


	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;

	// initiallizing ALLEGRO
	if (!al_init())
	{
		return -1;
	}
	// Creating display object
	display = al_create_display(width, height);
	//testing display obj
	if (!display)
	{
		return -1;
	}
	//initializing addons
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	//==============================================
	//PROJECT INIT
	//==============================================
	font18 = al_load_font("arial.ttf", 18, 0);

	//loading the Start Screen
	start = al_load_bitmap("start.png");
	imageWidth = al_get_bitmap_width(start);
	imageHeight = al_get_bitmap_height(start);

	//loading Pause screen
	pause = al_load_bitmap("pausescreen.bmp");
	imageWidth = al_get_bitmap_width(pause);
	imageHeight = al_get_bitmap_height(pause);
	
	// loading GAMEOVER screen
	gameover = al_load_bitmap("wasted screen.png");
	imageWidth = al_get_bitmap_width(gameover);
	imageHeight = al_get_bitmap_height(gameover);


	//Timer initialize and startup
	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	gameTime = al_current_time();

	while (!done)
	{
		ALLEGRO_EVENT evnt;
		al_wait_for_event(event_queue, &evnt);

		if (evnt.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evnt.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = true;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = true;
				break;
			}
		}

		else if (evnt.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (evnt.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				keys[ESCAPE] = false;
				break;
			case ALLEGRO_KEY_ENTER:
				keys[ENTER] = false;
				break;
			}
		}
		

		//GAME UPDATE
		
		else if (evnt.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;


			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}

			if (page == MENU)
			{
				if (keys[ENTER])
					page = PLAYING;

				if (keys[ESCAPE])
					done = true;
			}


			if (page == PLAYING)
			{
				if (keys[ESCAPE])
					page = PAUSE;
			}


			if (page ==PAUSE)
			{
				if (keys[ENTER])
					page = PLAYING;
				if (keys[SPACE])
					page = MENU;

				if (keys[ESCAPE])
					done = true;

			}

		
			if (page == GAMEOVER)
			{
				if (keys[ENTER])
					page = MENU;

				if (keys[ESCAPE])
					done = true;
				
			}
		}
			
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			
			
			if (page==MENU)
			{ 
				al_draw_bitmap(image, width / 2 - imageWidth / 2, height / 2 - imageHeight / 2, 0);

			}
			if (page == PLAYING)
			{
			}

			if (page == PAUSE)
			{
				al_draw_bitmap(pause, width / 2 - imageWidth / 2, height / 2 - imageHeight / 2, 0);

			}
			if (page == GAMEOVER)
			{
				al_draw_bitmap(gameover, width / 2 - imageWidth / 2, height / 2 - imageHeight / 2, 0);

			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	//Destroying objects
	al_destroy_bitmap(image);
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

void ChangePage(int &page, int newPage);

/*NB!!!!!!!!!!!!!!!!!!!!!!!!! check loading bitmaps with allegro 5 by MikeGeigTv*/