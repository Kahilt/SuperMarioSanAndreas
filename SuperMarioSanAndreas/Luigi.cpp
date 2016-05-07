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
		alive = true;
		aniWidth = 125.0;
		aniHeight = 185.0;

		health = 10;
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

	void drawHealth(ALLEGRO_BITMAP *healthBar)	//draws the health status of Luigi
	{
		if (health == 10)
			al_draw_bitmap_region(healthBar, 0, 0, 264, 22, x - 20, y - 50, NULL);
		else if (health == 9)
			al_draw_bitmap_region(healthBar, 0, 22, 264, 28, x - 20, y - 50, NULL);
		else if (health == 8)
			al_draw_bitmap_region(healthBar, 0, 50, 264, 29, x - 20, y - 50, NULL);
		else if (health == 7)
			al_draw_bitmap_region(healthBar, 0, 79, 264, 32, x - 20, y - 50, NULL);
		else if (health == 6)
			al_draw_bitmap_region(healthBar, 0, 111, 264, 33, x - 20, y - 50, NULL);
		else if (health == 5)
			al_draw_bitmap_region(healthBar, 0, 144, 264, 29, x - 20, y - 50, NULL);
		else if (health == 4)
			al_draw_bitmap_region(healthBar, 0, 173, 264, 31, x - 20, y - 50, NULL);
		else if (health == 3)
			al_draw_bitmap_region(healthBar, 0, 204, 264, 33, x - 20, y - 50, NULL);
		else if (health == 2)
			al_draw_bitmap_region(healthBar, 0, 237, 264, 34, x - 20, y - 50, NULL);
		else if (health == 1)
			al_draw_bitmap_region(healthBar, 0, 271, 264, 32, x - 20, y - 50, NULL);
		else if (health == 0)
		{
			al_draw_bitmap_region(healthBar, 0, 303, 264, 25, x - 20, y - 50, NULL);
			x = -1000;		//removes luigi from game window
			y = -1000;
			alive = false;		//luigi dead
		}

		/*if (check)			//used to test health bar
		{
			health -= 1;
			if (health == 0)
				health = 10;
		}*/
	}
};