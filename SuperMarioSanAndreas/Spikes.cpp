#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
#include "world obstacles.cpp"
class Spikes : public worldObstacles
{
private:

	float x;
	float y;

public:
	float spikeL;
	float spikeW;

	int spikeType;		

	void draw(ALLEGRO_BITMAP *s1, ALLEGRO_BITMAP *s2, ALLEGRO_BITMAP *s3)
	{
		if (spikeType == 1){
			al_draw_bitmap(s1, x, y, NULL);
		}
		else if (spikeType == 2){
			al_draw_bitmap(s2, x, y, NULL);
		}
		else
			al_draw_bitmap(s3, x, y, NULL);
	}
	void setvalue(int posx, int posy, int type)
	{
		x = posx;
		y = posy;
		spikeType = type;
	}
};