#ifndef WORLDOBSTACLES_HEADER
#define WORLDOBSTACLES_HEADER

#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
using namespace std;

class worldObstacles{
public:
	virtual void draw(ALLEGRO_BITMAP *x, ALLEGRO_BITMAP *y, ALLEGRO_BITMAP *z){};
	virtual void setvalue(int a, int b, int c) = 0;

};
#endif