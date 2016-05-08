#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <cmath>

using namespace std;


class Enemies
{
public:
	float x;			//contains current x value of enemy
	float y;			//contains current y value of enemy

	float startX;		//since enemies move back and forth on a fixed path, staring and ending positions are needed
	float endX;

	float direction;	//used to determine whether enemy is moving left or right (+1 for right, -1 for left)

	float aniWidth;		//contains width of animation in pixels
	float aniHeight;		//contains height of animation in pixels

	bool alive;			//determines whether enemy is alive or dead

	float sourceX;		//sourceX to control which portion of the sprite is printed
	int type;			//	1 = Punching gangster,	2 = Chain gangster

	Enemies()
	{
		startX = -1000;		//ensures that stage is initially clear
		x = startX;			//allows enemy to start at specified starting point
		y = 0;
		direction = 1;		//initial direction set to RIGHT
		bool alive = true;
		sourceX = 0;
		type = 1;

		aniHeight = 120.0;
		aniWidth = 110.0;
	}


	~Enemies()
	{
	}

	void setValues(float xPos, float yPos, float stX, float enX,int ty)		//allows main program to alter values of object
	{
		x = xPos;
		y = yPos;
		startX = stX;
		endX = enX;
		type = ty;

		if (type == 2)
		{
			aniWidth = 140.0;
			aniHeight = 130.0;
		}
	}

	void move(int speed)
	{
		
		if (x <= startX)		//if enemy tries to go before starting point, direction is changed
			direction = 1.0;

		if (x > endX)		//if enemy tries to go after starting point, direction is changed
			direction = -1.0;

		x += (direction * speed);		//increments enemy's position 
	}

	void getHitWithHammer(ALLEGRO_BITMAP *punch, ALLEGRO_BITMAP *chain, ALLEGRO_BITMAP *mario, float mx, float my, float m_width, float m_height, bool hit_check)
	{
		if (type == 1)
		{
			if ((x + aniWidth < mx || x > mx + m_width || y + aniWidth < my || y > my + m_height) && hit_check == false)
			{
				//do nothing since no contact
			}
			else
			{
				float top = max(y, my);					//calculates collision area
				float bottom = min(y + aniHeight, my + m_height);
				float left = max(x, mx);
				float right = min(x + aniWidth, mx + m_width);

				for (int i = top; i < bottom; i++)		//traverses through each pixel in collision area
				{
					for (int j = left; j < right; j++)
					{
						al_lock_bitmap(punch, al_get_bitmap_format(punch), ALLEGRO_LOCK_READONLY);
						al_lock_bitmap(mario, al_get_bitmap_format(mario), ALLEGRO_LOCK_READONLY);

						ALLEGRO_COLOR col = al_get_pixel(punch, j - x, i - y);
						ALLEGRO_COLOR m_col = al_get_pixel(mario, j - mx, i - my);

						if (col.a != 0 && m_col.a != 0 && hit_check == true)			//collision is true
						{
							alive = false;
							x = -1000;
							y = -1000;
							startX = -1000;
							endX = -1000;
						}
					}
				}

			}
		}
		else
		{
			if ((x + aniWidth < mx || x > mx + m_width || y + aniWidth < my || y > my + m_height) && hit_check == false)
			{
				//do nothing since no contact
			}
			else
			{
				float top = max(y, my);					//calculates collision area
				float bottom = min(y + aniHeight, my + m_height);
				float left = max(x, mx);
				float right = min(x + aniWidth, mx + m_width);

				for (int i = top; i < bottom; i++)		//traverses through each pixel in collision area
				{
					for (int j = left; j < right; j++)
					{
						al_lock_bitmap(chain, al_get_bitmap_format(chain), ALLEGRO_LOCK_READONLY);
						al_lock_bitmap(mario, al_get_bitmap_format(mario), ALLEGRO_LOCK_READONLY);

						ALLEGRO_COLOR col = al_get_pixel(chain, j - x, i - y);
						ALLEGRO_COLOR m_col = al_get_pixel(mario, j - mx, i - my);

						if (col.a != 0 && m_col.a != 0 && hit_check == true)			//collision is true
						{
							alive = false;
							x = -1000;
							y = -1000;
							startX = -1000;
							endX = -1000;
						}
					}
				}

			}

		}
	}

	void draw(ALLEGRO_BITMAP *punch, ALLEGRO_BITMAP *chain, bool time)	//receives an ALLEGRO_BITMAP from game loop, time controls how often animation changes
	{
		if (alive)
		{
			if (type == 1)			//draws appropriate animation for punching gangster
			{
				if (direction == 1)
				{
					if (!punch)
						cout << "Error loading image";

					if (time)
						sourceX += al_get_bitmap_width(punch) / 7;		//since there are 7 animations 

					if (sourceX >= al_get_bitmap_width(punch))		//sets source point back to 0 when end is reached
						sourceX = 0;

					al_draw_bitmap_region(punch, sourceX, 121, aniWidth, aniHeight, x, y, NULL);		//draws image
				}
				else
				{
					if (time)
						sourceX += al_get_bitmap_width(punch) / 7;		//since there are 7 animations 

					if (sourceX >= al_get_bitmap_width(punch))		//sets source point back to 0 when end is reached
						sourceX = 0;

					al_draw_bitmap_region(punch, sourceX, 0, aniWidth, aniHeight, x, y, NULL);		//draws image
				}
			}
			else if (type == 2)			//draws appropriate image for chain gangster
			{
				if (direction == 1)
				{
					if (!chain)
						cout << "Error loading image";

					if (time)
						sourceX += al_get_bitmap_width(chain) / 13;		//since there are 13 animations 

					if (sourceX >= al_get_bitmap_width(chain))		//sets source point back to 0 when end is reached
						sourceX = 0;

					al_draw_bitmap_region(chain, sourceX, 131, aniWidth, aniHeight, x, y, NULL);		//draws image
				}
				else
				{
					if (time)
						sourceX += al_get_bitmap_width(chain) / 13;		//since there are 13 animations 

					if (sourceX >= al_get_bitmap_width(chain))		//sets source point back to 0 when end is reached
						sourceX = 0;

					al_draw_bitmap_region(chain, sourceX, 0, aniWidth, aniHeight, x, y, NULL);		//draws image
				}
			}
		}
	}


};


//code for normal Mario

/*
ALLEGRO_BITMAP *currMario;

if (check2 == 1)
					{
						currMario = al_create_sub_bitmap(AttackR, sourceXj + 100 , 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x + 89, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					else
					{
						currMario = al_create_sub_bitmap(AttackL, sourceXi, 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x - 148, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
						}*/