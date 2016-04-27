#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
#include "world obstacles.cpp"
class Cars : public worldObstacles
{
private:

	float x;
	float y;

public:
	float carsHeight;
	float carsWidth;

	int size;		//1= small ,2= medium, 3 = large

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