#pragma once
#include <allegro5/allegro.h> //telling vs we are using allegro functions
#include <iostream> //used for keyboard input and output
#include <allegro5/allegro_image.h> //used for animations and insertion of images
using namespace std;

class SuperMario
{
public:
	
	int sourceX , sourceY ;//used for cropping the SpriteSheet for animation

	bool draw ;//for timer, used for smooth animations
	float x , y , moveSpeed ; // x and y are starting co-ordinates of Mario, moveSpeed is the increment of the co-ordinates hence will det how fast Mario moves

	


	void startMovement(ALLEGRO_DISPLAY *, bool, ALLEGRO_EVENT, ALLEGRO_KEYBOARD_STATE, ALLEGRO_BITMAP *);
	void drawMario(bool draw, ALLEGRO_BITMAP *player)
	{
		
	}
	SuperMario(float xPos, float yPos)
	{
		sourceX = 0;
		sourceY = 0;
		x = xPos;
		y = yPos;//starting co-ordinates on (x;y) is (xPos;yPos)
	}
	~SuperMario()
	{
	}
};
