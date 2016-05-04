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

void SuperMario::startMovement(ALLEGRO_DISPLAY *display, bool done, ALLEGRO_EVENT events, ALLEGRO_KEYBOARD_STATE keyState, ALLEGRO_BITMAP *player)
{
	if (events.type == ALLEGRO_EVENT_KEY_DOWN)
	{
		switch (events.keyboard.keycode)
		{
		case ALLEGRO_KEY_ESCAPE:
			done = true;
			break;
		}
	}
	else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		done = true;


	if (events.type == ALLEGRO_EVENT_TIMER)
	{
		active = true;
		al_get_keyboard_state(&keyState);
		if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
		{
			y += 3;
			dir = DOWN;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT) && al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			x -= 3;
			y -= 8;
			dir = UP;
			check = 2;

		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT) && al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			x += 3;
			y -= 8;
			dir = UP;
			check = 2;

		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
		{
			y -= 8;
			dir = UP;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
		{
			x += moveSpeed;
			dir = RIGHT;
			check = 1;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
		{
			x -= moveSpeed;
			dir = LEFT;
			check = 2;
		}

		else if (!al_key_down(&keyState, NULL))
		{
			if (check == 1 || check == 0)
			{

				if (y != 400)
				{
					y += 3;
				}
				dir = NONE1;
			}
			else
			{
				if (y != 400)
				{
					y += 3;
				}
				dir = NONE2;
			}
		}
		else active = false;

		if (active)
			sourceX += al_get_bitmap_width(player) / 3;

		if (sourceX >= al_get_bitmap_width(player))
			sourceX = 0;
	}

}