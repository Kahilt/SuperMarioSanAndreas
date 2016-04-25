#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>	
using namespace std;
#define width 800
#define length 600
int main()
{
	ALLEGRO_DISPLAY *display;
	if (!al_init())
	{
		al_show_native_message_box(NULL, NULL, NULL, "Unable to initialize allegro %", NULL, NULL);
			return -1;
	}
	display = al_create_display(width, length);

	if (!display)
	{
		al_show_native_message_box(display, "Sample Title", "Display Settings", "Unable to display");
	}
	al_destroy_display(display);
	return 0;


}