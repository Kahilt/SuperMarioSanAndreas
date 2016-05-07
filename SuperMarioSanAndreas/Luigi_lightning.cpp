#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

using namespace std;
class Luigi_lightning
{
public:
	float x;			//starts at point just before Luigi
	float y;			//starts at y position of luigi's hand

	float sourceX[7];		//contains width and height of animations
	float tempX;			//controls the source point of ther animations
	int i;					//used to iterate array
	bool active;

	Luigi_lightning()
	{
		x = -1000;
		y = -1000;

		sourceX[6] = 60;		//width of each animation
		sourceX[5] = 165;
		sourceX[4] = 417;
		sourceX[3] = 642;
		sourceX[2] = 645;
		sourceX[1] = 648;
		sourceX[0] = 636;

		tempX = 3153;
		i = 6;

		active = false;
	}

	~Luigi_lightning()
	{

	}

	void draw(ALLEGRO_BITMAP *light, bool time)
	{
		if (active)
		{
			al_draw_bitmap_region(light, tempX, 0, sourceX[i], 112, (x - sourceX[i]), y, NULL);

			if (time)
			{
				i--;

				tempX -= sourceX[i];

				if (i == -1)		//used to set i back to ending of array
				{
					i = 6;
					tempX = 3153;
					active = false;
				}
			}
		}
	}

	
};