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

	int cartype;		//1= muscle car ,2= cop car, 3 = bus

		void draw(ALLEGRO_BITMAP *muscle, ALLEGRO_BITMAP *cop, ALLEGRO_BITMAP *bus)
	{
		if (cartype == 1){
			al_draw_bitmap(muscle, x, y, NULL);
		}
		else if (cartype == 2){
			al_draw_bitmap(cop, x, y, NULL);
		}
		else
			al_draw_bitmap(bus, x, y, NULL);
	}
	void setvalue(int posx, int posy, int type)
	{
		x = posx;
		y = posy;
		cartype = type;
	}
	void drawMulti(int startloop, int endloop, int plusplus)
	{
		int val = 0;
		for (int i = startloop; i < endloop; i++){
			setvalue(x, y, cartype);
			val +=plusplus;

		}
	}
};