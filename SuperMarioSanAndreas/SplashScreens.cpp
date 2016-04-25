#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <iostream> 
#include <allegro5\allegro_image.h>

using namespace std;

int splash()
{
	//creating variables to be used
	int width = 1366;
	int height = 770;
	bool done = false;
	int imageWidth = 0;
	int imageHeight = 0;


	//creating allegro variables
	ALLEGRO_DISPLAY *display= NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
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
	//initializing addons
	al_install_keyboard();
	al_init_image_addon();

	//inserting the image
	image = al_load_bitmap("startscreen.png");
	imageWidth = al_get_bitmap_width(image);
	imageHeight = al_get_bitmap_height(image);
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	
	while (!done)
	{
		ALLEGRO_EVENT evnt;
		al_wait_for_event(event_queue, &evnt);

		if (evnt.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (evnt.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}
		al_draw_bitmap(image, width / 2 - imageWidth / 2, height / 2 - imageHeight / 2, 0);
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//Destroying objects
	al_destroy_bitmap(image);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);
	return 0;
}

/*NB!!!!!!!!!!!!!!!!!!!!!!!!! check loading bitmaps with allegro 5 by MikeGeigTv*/