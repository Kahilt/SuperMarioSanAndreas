#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
#include "world obstacles.cpp"
class manHole : public worldObstacles
{
private:

	

public:
	float x;
	float y;

	float manholeL;
	float manholeW;

	int manholeType;		//1= muscle car ,2= cop car, 3 = bus

	void draw(ALLEGRO_BITMAP *m1, ALLEGRO_BITMAP *m2, ALLEGRO_BITMAP *m3)
	{
		if (manholeType == 1){
			al_draw_bitmap(m1, x, y, NULL);
		}
		else if (manholeType == 2){
			al_draw_bitmap(m2, x, y, NULL);
		}
		else
			al_draw_bitmap(m3, x, y, NULL);
	}
	void setvalue(int posx, int posy, int type)
	{
		x = posx;
		y = posy;
		manholeType = type;
	}
};