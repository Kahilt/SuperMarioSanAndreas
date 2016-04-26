#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>

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

	Enemies()
	{
		startX = -1000;		//ensures that stage is initially clear
		x = startX;			//allows enemy to start at specified starting point
		y = 0;
		direction = 1;		//initial direction set to RIGHT
		bool alive = true;
		sourceX = 0;

		aniHeight = 120.0;
		aniWidth = 110.0;
	}


	~Enemies()
	{
	}

	void move(int speed)
	{
		
		if (x <= startX)		//if enemy tries to go before starting point, direction is changed
			direction = 1.0;

		if (x > endX)		//if enemy tries to go after starting point, direction is changed
			direction = -1.0;

		x += (direction * speed);		//increments enemy's position 
	}

	void getShot(/*		will receive a Bullet object		*/)
	{
		//check if bullet collides with enemy, if true : alive = false;
	}

	void draw(ALLEGRO_BITMAP *enemy, bool time)	//receives an ALLEGRO_BITMAP from game loop, time controls how often animation changes
	{
		if (alive)
		{
			if (direction == 1)
			{
				if (!enemy)
					cout << "Error loading image";

				if (time)
					sourceX += al_get_bitmap_width(enemy) / 7;		//since there are 7 animations 

				if (sourceX >= al_get_bitmap_width(enemy))		//sets source point back to 0 when end is reached
					sourceX = 0;
	
				al_draw_bitmap_region(enemy, sourceX, 121, aniWidth, aniHeight, x, y, NULL);		//draws image
			}
			else
			{
				if (time)
					sourceX += al_get_bitmap_width(enemy) / 7;		//since there are 7 animations 

				if (sourceX >= al_get_bitmap_width(enemy))		//sets source point back to 0 when end is reached
					sourceX = 0;

				al_draw_bitmap_region(enemy, sourceX, 0, aniWidth, aniHeight, x, y, NULL);		//draws image
			}
		}
	}


};
