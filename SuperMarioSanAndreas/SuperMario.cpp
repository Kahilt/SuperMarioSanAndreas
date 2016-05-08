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
	bool marioCollide(float x, float y, float ex, float ey, int len, int height, ALLEGRO_BITMAP *player, ALLEGRO_BITMAP *enemy)
{
	if (x+len<ex||x>ex+len||y+height<ey||y>ey+height)
		return false;
	else
	{
		top = max(y, ey);
		bot = min(y + height, ey + height);
		lef= max(x, ex);
		righ = min(x + len, ex + len);
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
}
};






