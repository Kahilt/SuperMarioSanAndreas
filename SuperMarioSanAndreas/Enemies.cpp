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

	float width;		//contains width of animation in pixels
	float height;		//contains height of animation in pixels

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

		height = 120.0;
		width = 110.0;
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

	void draw(ALLEGRO_BITMAP *right , ALLEGRO_BITMAP *left)	//receives an ALLEGRO_BITMAP from game loop
	{
		if (alive)
		{
			//al_init_image_addon();																			*in game loop
			//ALLEGRO_BITMAP *punch_ganster_right = al_load_bitmap("Punching_gangster_RIGHT.png");				*in game loop
			//ALLEGRO_BITMAP *punch_ganster_left = al_load_bitmap("Punching_gangster_LEFT.png");				*in game loop

			if (direction == 1)
			{
				if (!right)
					cout << "Error loading image";

				sourceX += al_get_bitmap_width(right) / 7;		//since there are 7 animations 

				if (sourceX >= al_get_bitmap_width(right))		//sets source point back to 0 when end is reached
					sourceX = 0;
	
				al_draw_bitmap_region(right, sourceX, 0, width, height, x, y, NULL);		//draws image
			}
			else
			{
				if (!left)
					cout << "Error loading image";

				sourceX += al_get_bitmap_width(left) / 7;		//since there are 7 animations 

				if (sourceX >= al_get_bitmap_width(left))		//sets source point back to 0 when end is reached
					sourceX = 0;

				al_draw_bitmap_region(left, sourceX, 0, width, height, x, y, NULL);		//draws image
			}
		}
	}


};
