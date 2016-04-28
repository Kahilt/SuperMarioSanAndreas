#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


using namespace std;
//###################################################
// VARIABLE CREATION
//###################################################
const int width = 1366;
const int height = 770;
int imageWidth = 0;
int imageHeight = 0;

bool keys[] = { false, false, false };
enum KEYS{ ENTER, ESCAPE, SPACE};
enum PAGE{ MENU, PLAYING, PAUSE, GAMEOVER };
 
void ChangePage(int &page, int newPage);


int splash(int argc, char **argv)
{
	bool done = false;
	bool render = false;
	float gameTime = 0;
	int frames = 0;
	int gameFPS = 0;

	//PROJECT VARIABLES
	int page = -1;

	//CREATING ALLEGRO VARIABLES
	ALLEGRO_DISPLAY *display= NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *start = NULL;
	ALLEGRO_BITMAP *pause = NULL;
	ALLEGRO_BITMAP *gameover = NULL;
	ALLEGRO_BITMAP *image=NULL ;


	ALLEGRO_TIMER *timer;
	ALLEGRO_FONT *font18;

	//###################################################
	// INITIALIZING ALLEGRO
	//###################################################
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


	//###################################################
	// INITAILIZING ADDONS
	//###################################################
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();


	//###################################################
	// INITIALIZING PROJECT
	//###################################################
	font18 = al_load_font("arial.ttf", 18, 0);

	//###################################################
	// LOADING ALL SCREEN PICTURES
	//###################################################
	//loading the Start Screen
	start = al_load_bitmap("start.png");
	
	//loading Pause screen
	pause = al_load_bitmap("pausescreen.bmp");
	
	// loading GAMEOVER screen
	gameover = al_load_bitmap("wasted screen.png");
	

	ChangePage(page, MENU);

	//###################################################
	// TIMER INITIALIZATION AND STARTUP
	//###################################################
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
		


		//###################################################
		//GAME UPDATES
		//###################################################
		
		else if (evnt.type == ALLEGRO_EVENT_TIMER)
		{
			render = true;

			//FPS UPDATE
			frames++;
			if (al_current_time() - gameTime >= 1)
			{
				gameTime = al_current_time();
				gameFPS = frames;
				frames = 0;
			}
			//###################################################
			// PAGES SECTION
			//###################################################
			if (page == MENU)
			{
				al_draw_bitmap(start, 0, 0, 0);
				if (keys[ENTER])
					
					ChangePage(page,PLAYING);

				else if (keys[ESCAPE])
					done = true;
			}


			else if (page == PLAYING)
			{
				if (keys[ESCAPE])
					ChangePage(page, PAUSE);
			}


			else if (page ==PAUSE)
			{
				al_draw_bitmap(pause, 0, 0, 0);
				if (keys[ENTER])
					ChangePage(page, PLAYING);
				else if (keys[SPACE])
					ChangePage(page, MENU);

				else if (keys[ESCAPE])
					done = true;

			}

		
			else if (page == GAMEOVER)
			{
				al_draw_bitmap(gameover, 0, 0, 0);
				if (keys[ENTER])
					ChangePage(page, MENU);

				else if (keys[ESCAPE])
					done = true;
				
			}
		}

		//###################################################
		// RENDER SECTION
		//###################################################
		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;
			
			
			if (page==MENU)
			{ 
				al_draw_bitmap(start,0,0,0);

			}
			if (page == PLAYING)
			{
			}

			if (page == PAUSE)
			{
				al_draw_bitmap(pause, 0, 0, 0);
			}
			if (page == GAMEOVER)
			{
				al_draw_bitmap(gameover, 0,0,0);

			}

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	//Destroying objects
	al_destroy_bitmap(image);
	al_destroy_bitmap(start);
	al_destroy_bitmap(pause);
	al_destroy_bitmap(gameover);
	al_destroy_font(font18);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

//###################################################
// OPTIONAL PART
//###################################################


/*void ChangePage(int &page, int newPage)
{
	if (page == MENU)
	{
		std::cout << "Leaving menu\n";
	}
	else if (page == PLAYING)
	{
		std::cout << "Leaving gameplay\n";
	}
	else if (page == PAUSE)
	{
		std::cout << "Leaving pause screen\n";
	}
	else if (page == GAMEOVER)
	{
		std::cout << "Leaving the game\n";
	}

	page = newPage;

	if (page == MENU)
	{
		std::cout << "Entering Menu\n";
	}
	else if (page == PLAYING)
	{
		std::cout << "Entering gameplay\n";
	}
	else if (page == PAUSE)
	{
		std::cout << "Entering pause screen\n";
	}
	else if (page == GAMEOVER)
	{
		std::cout << "Entering gameover screen\n";
	}
}
*/
/*NB!!!!!!!!!!!!!!!!!!!!!!!!! check loading bitmaps with allegro 5 by MikeGeigTv*/