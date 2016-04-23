#include <allegro5/allegro.h>
#include <iostream> 
#include <allegro5/allegro_image.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
using namespace std;
#define length 1366
#define width 775

 int main(){

	 al_init();

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(length, width);
	al_set_window_position(display, 200, 100);
	al_init_image_addon();
	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("bg.png");
	ALLEGRO_BITMAP *imagewindowsky = al_load_bitmap("Sky.png");
	ALLEGRO_BITMAP *imagemusclecar = al_load_bitmap("mcar.png");
	ALLEGRO_BITMAP *imagecopcar = al_load_bitmap("ccar.png");
	
	

	al_draw_bitmap(imagewindowsky, 1, 2, NULL);
	al_draw_bitmap(imagewindow, 1, 5, NULL);
	
	al_draw_bitmap(imagemusclecar, 175, 553, NULL);
	al_draw_bitmap(imagecopcar, 700, 635, NULL);
	
	
	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	
	al_flip_display();
	al_rest(10);
	//al_destroy_font(font);
	al_destroy_display(display);
	return 0;
}