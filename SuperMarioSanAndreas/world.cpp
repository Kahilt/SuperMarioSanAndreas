#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
using namespace std;
#define length 800
#define width 600
 int main(){

	 al_init();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(length, width);
	al_set_window_position(display, 200, 100);
	al_init_image_addon();
	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("ylogo114.jpg");
	ALLEGRO_BITMAP *imagewindowRoad = al_load_bitmap("road-clipart-cliparti1_road-clip-art_07.jpg");

	al_draw_bitmap(imagewindow, 1, 1, NULL);
	al_draw_bitmap(imagewindowRoad, 1, 450, NULL);

	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	//al_draw_text(font, al_map_rgb(44, 117, 255), width / 2, length/4, ALLEGRO_ALIGN_CENTRE, "KESHAV JEEWANLALL");
	al_flip_display();
	al_rest(10);
	//al_destroy_font(font);
	al_destroy_display(display);
	return 0;
}