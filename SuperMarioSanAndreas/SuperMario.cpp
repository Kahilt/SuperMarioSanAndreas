#include "SuperMario.h"


SuperMario::SuperMario()
{
	sourceX = 0;
	sourceY = 0;
	alive = false;
	active = false;
	draw = true;
	x = 10;
	y = 10;//starting co-ordinates on (x;y) is (10;10)
	moveSpeed = 5;
	check = 0;
	dir = DOWN;//the initial direction of Mario is set to down
}


SuperMario::~SuperMario()
{
}
