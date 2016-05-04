#include "SuperMario.h"


SuperMario::SuperMario(float xPos,float yPos)
{
	sourceX = 0;
	sourceY = 0;
	dead = false;
	active = false;
	draw = true;
	x = xPos;
	y = yPos;//starting co-ordinates on (x;y) is (xPos;yPos)
	moveSpeed = 5;
	check = 0;
	dir = RIGHT;//the initial direction of Mario is set to down
}


SuperMario::~SuperMario()
{
}

void SuperMario::startMovement(ALLEGRO_DISPLAY *display)
{
	al_install_keyboard();
	ALLEGRO_KEYBOARD_STATE keyState;
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();// create pointer for keyboard
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS); //event 1/60 sec, the game will update
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //stores the keyboard buttons in a queue to be executed
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_start_timer(timer);
}
