#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>	
using namespace std;
#define width 770
#define length 1366
int splash()
{
	ALLEGRO_DISPLAY *display;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Unable to initialize allegro 5", NULL, NULL);
			return -1;
	}
	display = al_create_display(width, length);

	if (!display)
	{
		al_show_native_message_box(display, "Sample Title", "Display Settings", "Unable to display",NULL,NULL);
	}
	al_destroy_display(display);
	


}