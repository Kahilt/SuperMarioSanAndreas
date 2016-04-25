#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>	
using namespace std;

int splash()
{
	//creating variables to be used
	int width = 1366;
	int height = 770;
	bool done = false;
	//creating allegro variables
	ALLEGRO_DISPLAY *display= NULL;
	ALLEGRO EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_BITMAP *image = NULL;
	
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
	al_install_keyboard();

	
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	while (!done)
	{
		ALLEGRO_EVENT evnt;
		al_wait_for_an_event(event_queue, &envt);

		if (evnt.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evnt.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//Destroying objects
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}