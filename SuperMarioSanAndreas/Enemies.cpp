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

	void draw(ALLEGRO_BITMAP *en)	//receives an ALLEGRO_BITMAP from game loop
	{
		if (alive)
		{
			//al_init_image_addon();				*in game loop

			//ALLEGRO_BITMAP *en = al_load_bitmap("Enemy.png");				*in game loop

			if (!en)
				cout << "Error loading image";

			sourceX += al_get_bitmap_width(en) / 3;		//assuming sprite has 3 animations, source point increments by on animation length each time

			if (sourceX >= al_get_bitmap_width(en))		//sets source point back to 0 when end is reached
				sourceX = 0;

			al_draw_bitmap_region(en, sourceX, 0, width, height, x, y, NULL);		//draws image
			al_rest(10.0);
		}
	}


};
