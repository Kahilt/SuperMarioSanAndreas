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
	
}
