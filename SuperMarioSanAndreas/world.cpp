#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
using namespace std;
#define length 800
#define width 600
 int main(){

	 al_init();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(length, width);
	al_set_window_position(display, 200, 100);
	ALLEGRO_COLOR screenColour = al_map_rgb(0, 255, 0);
	al_clear_to_color(screenColour);
	al_rest(5.0);
	al_destroy_display(display);
	return 0;
}