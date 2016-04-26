#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives

class Cars
{

public:
	float caright;
	float carWidth;

	float x;
	float y;

	int carType;		//1= Muscle car ,2= Cop car

	Cars()
	{
		x = -1000;
		y = -1000;

		carWidth = 86.0;
		carType = 1;				
	}

	void setCars(int posx, int posy, int type)
	{
		x = posx;
		y = posy;
		carType = type;
	}

	~Cars()
	{

	}

	void draw(ALLEGRO_BITMAP *muscle, ALLEGRO_BITMAP *cop)
	{
		if (carType == 1){
			al_draw_bitmap(muscle, x, y, NULL);
		}
		
		else{
			al_draw_bitmap(cop, x, y, NULL);
		}
	}
};
