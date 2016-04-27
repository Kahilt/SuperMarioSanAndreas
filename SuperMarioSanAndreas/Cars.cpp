#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
#include "world obstacles.cpp"
class Cars : public worldObstacles
{

public:
	float carsHeight;
	float carsWidth;

	float x;
	float y;

	int size;		//1= small ,2= medium, 3 = large

	/*pilars()
	{
	x = -1000;
	y = -1000;

	carsWidth = 86.0;
	size = 1;				//all pilars are assumed small initially
	}

	~pilars()
	{

	}*/

	void draw(ALLEGRO_BITMAP *muscle, ALLEGRO_BITMAP *cop)
	{
		if (size == 1){
			al_draw_bitmap(muscle, x, y, NULL);
		}
		else{
			al_draw_bitmap(cop, x, y, NULL);
		}
	}
	void setvalue(int posx, int posy, int type)
	{
		x = posx;
		y = posy;
		size = type;
	}
};