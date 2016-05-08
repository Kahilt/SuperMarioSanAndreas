#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cmath>
class SuperMario{

public:
	int top, bot, lef, righ;
	bool marioCollide(float x, float y, float ex, float ey, int len, int height, ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy, int el, int eh)
	{
	if (x+len<ex||x>ex+el||y+height<ey||y>ey+eh)
		return false;
	else
	{
		top = max(y, ey);
		bot = min(y + height, ey + eh);
		lef= max(x, ex);
		righ = min(x + len, ex + el);
		for (int i= top; i < bot; i++)
		{
			for (int j = lef; j < righ; j++)
			{
				al_lock_bitmap(player, al_get_bitmap_format(player), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(enemy, al_get_bitmap_format(enemy), ALLEGRO_LOCK_READONLY);
				ALLEGRO_COLOR color = al_get_pixel(player, j - x, i - y);
				ALLEGRO_COLOR color2 = al_get_pixel(enemy, j - ex, i - ey);
				if (color.a != 0 && color2.a != 0)
				{
					return true;//die
				}
			}
		}
	}
	return false;
	}

	bool spikeCollision(ALLEGRO_BITMAP *mario, ALLEGRO_BITMAP * spike, int x, int y, int wid, int hei, int sx, int sy , int sw , int sh)
	{
		if (x + wid < sx || x > sx + sw || y + hei < sy || y > sy + sh)
			return false;
		else
		{
			int top1 = max(y, sy);
			int bot1 = min(y + hei, sy + sh);
			int left = max(x, sx);
			int right = min(x + wid, sx + sw);

			for (int i = top1; i < bot1; i++)
			{
				for (int j = left; j < right; j++)
				{
					al_lock_bitmap(mario, al_get_bitmap_format(mario), ALLEGRO_LOCK_READONLY);
					al_lock_bitmap(spike, al_get_bitmap_format(spike), ALLEGRO_LOCK_READONLY);
					ALLEGRO_COLOR color = al_get_pixel(mario, j - x, i - y);
					ALLEGRO_COLOR color2 = al_get_pixel(spike, j - sx, i - sy);
					
					if (color.a != 0 && color2.a != 0)
					{
						return true;
					}
				}
			}
		}
	}
};






