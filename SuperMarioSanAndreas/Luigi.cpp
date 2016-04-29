#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>


class Luigi
{
public :
	float x;
	float y;

	float aniWidth;
	float aniHeight;

	float health;
	bool alive;

	float sourceX;

	Luigi()
	{
		x = -1000;
		y = -1000;

		aniWidth = 125.0;
		aniHeight = 185.0;

		health = 100;
		sourceX = 0;

	}

	~Luigi()
	{

	}

	void draw(ALLEGRO_BITMAP *luigi, bool time , bool light_active)
	{
		if (alive)
		{
			if (!light_active)
			{
				if (time)
					sourceX += al_get_bitmap_width(luigi) / 4;		//since there are 7 animations 
			}
				if (sourceX >= al_get_bitmap_width(luigi))		//sets source point back to 0 when end is reached

					sourceX = 0;

				al_draw_bitmap_region(luigi, sourceX, 0, aniWidth, aniHeight, x, y, NULL);		//draws image
		}
	}

	bool lightning_active()			//determines when lightning should be active. This occurs at last animation of Luigi
	{
		if (sourceX >= 375)
			return true;
		else
			return false;
	}
};