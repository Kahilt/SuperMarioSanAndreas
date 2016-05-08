#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <cmath>
using namespace std;
#define length 1366 //defining the screen length 
#define width 770  //defining the screen width 
#include "Enemies.cpp"
#include "pilars.cpp"
#include "Cars.cpp"
#include "world obstacles.cpp"
#include "manHoles.cpp"
#include "Luigi_lightning.cpp"
#include "Luigi.cpp"
#include "SuperMario.cpp"
#include "SplashScreens.cpp"
#include "Spikes.cpp"
void cameraUpdate(float *camerposition, float x, float y, int w, int h){
	camerposition[0] = -(length / 2) + (x + w / 2);				//positioning the camera at midpoint of the screen on the x axis
	if (camerposition[0] < 0)									//check if the position is less then zero and if true then make it equal to zero
		camerposition[0] = 0;
}
template<class first, class second>
void drawMulti(first startloop, first endloop, first plusplus,second object[],first posx,first posy,first type)
		{
			int val =0;
			for (int i = startloop; i < endloop; i++){
				object[startloop]->setvalue(posx + val, posy,type);
				val +=plusplus;

			}
		}
int top, bot, lef, righ;


 int main(){//main function

	 al_init();
	 int delay = 0;
	 bool hit = false;
	 bool hitcheck = false;

	 float sourceXa=0;//used for cropping the SpriteSheet for animation
	 float sourceXb = 0;
	 float sourceXc = 0;
	 float sourceXd = 0;
	 float sourceXe = 0;
	 float sourceXf = 0;
	 float sourceXg = 0;
	 float sourceXh = 0;
	 float sourceXi = 0;
	 float sourceXj = 0;
	 float velx, vely;
	 velx = 0;
	 vely = 0;
	 const float gravity=0.2;
	 bool jump = false;
	 float jumpSpeed = 20;
	 
	 //enum NewDirection{ RIGHT, LEFT, DOWN, UP, NONE1, NONE2 }; //Defines the different states or directions of mario. NONE1=facing right NONE2=facing left	
	 int moveSpeed = 10;
	 int check=1; //will record Marios last left or right movement to decide which side he will face after the key is left
	 int dir; //the initial direction of Mario is set to down
	// bool dead;//used to determine when mario will die
	 bool active; //will help cause the animation ONLY if key is pressed in particular direction
	 bool draw=false;//for timer, used for smooth animations
	 bool done = false;
	 int x = 0, y = 0, movespeed = 10;
	 int enemyMovespeed = 5;
	 int state = NULL;
	 const float FPS = 60.0;
	
	 const float EFPS = 15.0;		//controls speed of enemy animation
	 const float LFPS = 5.0;		//controls speed of Luigi animation
	 const float MFPS = 8.0;
	 const float WFPS = 9.0;
	 enum Direction {UP, DOWN, LEFT, RIGHT, NONE1, NONE2, ATT};
	 int level;//tells you what level you are currently drawing
	 const int numOfEnemys = 20;					//contains the number of enemies
	 bool jumpCheck;
	 int check2;
	// int dir = DOWN;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE);
	display = al_create_display(length, width);
	al_set_window_position(display, 0, 0);

	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
	float cameraposition[2] = { 0, 0 };

	ALLEGRO_KEYBOARD_STATE keyState;
	
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();// create pointer for keyboard
	
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //stores the keyboard buttons in a queue to be executed
	
	
	
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *mariotimer = al_create_timer(1.0 / MFPS); 

	ALLEGRO_TIMER *weapontimer = al_create_timer(1.0 /WFPS);
	ALLEGRO_TIMER *splash = al_create_timer(1.0 / 5.0);
	ALLEGRO_TIMER *enemyTimer = al_create_timer(1.0 / EFPS);			//controls the animation of enemies  
	ALLEGRO_TIMER *luigiTimer = al_create_timer(1.0 / LFPS);			//controls the animation of Luigi
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(mariotimer));
	al_register_event_source(event_queue, al_get_timer_event_source(splash));
	al_register_event_source(event_queue, al_get_timer_event_source(weapontimer));
	al_register_event_source(event_queue, al_get_timer_event_source(enemyTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(luigiTimer));
	ALLEGRO_TRANSFORM CAMERA;

	///////////////////////////////////////////////////////////////////////IMAGE LOADING/////////////////////////////////////////////////////////////
	ALLEGRO_BITMAP *start = al_load_bitmap("start.png");
	ALLEGRO_BITMAP *wasted = al_load_bitmap("wasted screen.png");
	ALLEGRO_BITMAP *Duck = al_load_bitmap("Duck.png");
	ALLEGRO_BITMAP *Jump = al_load_bitmap("Jump.png");
	ALLEGRO_BITMAP *Stand = al_load_bitmap("Stand.png");
	ALLEGRO_BITMAP *Walk = al_load_bitmap("Walk.png");
	ALLEGRO_BITMAP *Duck1 = al_load_bitmap("Duck1.png");
	ALLEGRO_BITMAP *Jump1 = al_load_bitmap("Jump1.png");
	ALLEGRO_BITMAP *Stand1 = al_load_bitmap("Stand1.png");
	ALLEGRO_BITMAP *Walk1 = al_load_bitmap("Walk1.png");
	ALLEGRO_BITMAP *AttackL = al_load_bitmap("attackleft.png");
	ALLEGRO_BITMAP *AttackR = al_load_bitmap("attackright.png");
	/////////////////////////////////////////////////////////////////////// SuperSaiyan Pics /////////////////////////////////////////////////////////////
	ALLEGRO_BITMAP *SuperDuckLeft = al_load_bitmap("superduckleft.png");
	ALLEGRO_BITMAP *SuperJumpLeft = al_load_bitmap("superjumpleft.png");
	ALLEGRO_BITMAP *SuperStandLeft = al_load_bitmap("superstandleft.png");
	ALLEGRO_BITMAP *SuperWalkLeft = al_load_bitmap("superwalkleft.png");
	ALLEGRO_BITMAP *SuperDuckRight = al_load_bitmap("superduckright.png");
	ALLEGRO_BITMAP *SuperJumpRight = al_load_bitmap("superjumpright.png");
	ALLEGRO_BITMAP *SuperStandRight = al_load_bitmap("superstandright.png");
	ALLEGRO_BITMAP *SuperWalkRight = al_load_bitmap("superwalkright.png");
	ALLEGRO_BITMAP *SuperAttackLeft = al_load_bitmap("newattackleft.png");
	ALLEGRO_BITMAP *SuperAttackRight = al_load_bitmap("newattackright.png");

	/////////////////////////////////////////////////////////////////////// End of SuperSaiyan Pics/////////////////////////////////////////////////////////////
	ALLEGRO_BITMAP *imagewindow = al_load_bitmap("bgc.png");
	ALLEGRO_BITMAP *imagewindowsky = al_load_bitmap("sky1.png");
	ALLEGRO_BITMAP *imagecar = al_load_bitmap("mcar.png");
	ALLEGRO_BITMAP *imagecopcar = al_load_bitmap("ccar.png");
	//ALLEGRO_BITMAP *mario = al_load_bitmap("Mario_Nintendo.png");
	ALLEGRO_BITMAP *punch_gangster = al_load_bitmap("Punching_gangster.png");
	ALLEGRO_BITMAP *chain_gangster = al_load_bitmap("Chain_gangster.png");
	ALLEGRO_BITMAP *imagebus = al_load_bitmap("bus.png");
	
	ALLEGRO_BITMAP *smallPillar = al_load_bitmap("brick_grey.png");
	ALLEGRO_BITMAP *medPillar = al_load_bitmap("download.png");
	ALLEGRO_BITMAP *manhole = al_load_bitmap("manhole.png");
	ALLEGRO_BITMAP *spike = al_load_bitmap("Spike.png");
	ALLEGRO_BITMAP *spikeflip = al_load_bitmap("Spike_flip.png");

	ALLEGRO_BITMAP *light = al_load_bitmap("Lightning sprite.png");
	ALLEGRO_BITMAP *luigiBM = al_load_bitmap("Luigi.png");
	ALLEGRO_BITMAP *luigiHealth = al_load_bitmap("Luigi_health_bar.png");

	ALLEGRO_BITMAP *currMario1;
	ALLEGRO_BITMAP *currMario2;

	///////////////////////////////////////////////////CALLING CLASSES/////////////////////////////////////////////////////////////////////////////

	SuperMario marioObject;

	Enemies gangster[numOfEnemys];						//creates 1 object of enemies class
	gangster[0].setValues(1000, 590, 1000, 1500,1);	//sets values to enemy
	gangster[1].setValues(1800, 590, 1800, 2200,1);
	gangster[2].setValues(3000, 600, 3000, 3800,2);
	gangster[3].setValues(4050, 600, 4080, 4800, 2);
	gangster[4].setValues(6500, 590, 5400, 5900, 1);
	gangster[5].setValues(6500, 590, 6000, 6700, 1);
	gangster[6].setValues(6500, 600, 7600, 8000, 2);
   
	Luigi luigi;						//Luigi positioned at end with lightning 
	luigi.x = 7500;
	luigi.y = 550;

	Luigi_lightning lightning;						
	lightning.x = luigi.x+10;
	lightning.y = luigi.y+40;

	
   
	///////////////////////setting values for the position of cars level 1//////////////////////////////////////////
	Cars car[20];
	
	worldObstacles *obstacleC[20];
	for (int i = 0; i < 20; i++)
	{
		obstacleC[i] = &car[i];
	}
	

	obstacleC[0]->setvalue(800, 650, 1);
	obstacleC[1]->setvalue(1600, 650, 1);
	obstacleC[2]->setvalue(2300, 650, 1);
	obstacleC[3]->setvalue(2800, 660, 2);
	obstacleC[4]->setvalue(3900, 660, 2);
	obstacleC[5]->setvalue(4900, 590, 3);
	
	///////////////////////setting values for the position of cars for level 2//////////////////////////////////////////
	obstacleC[6]->setvalue(800, 650, 1);
	obstacleC[7]->setvalue(1600, 650, 1);
	obstacleC[8]->setvalue(2300, 650, 1);
	//obstacleC[9]->setvalue(-2000, 800, 2);
	//obstacleC[10]->setvalue(3900, 660, 2);
	//obstacleC[11]->setvalue(4900, 590, 3);
	/*obstacle[12]->setvalue(, 590, 3);
	obstacle[13]->setvalue(4900, 590, 3); 
	obstacle[14]->setvalue(4900, 590, 3);*/

	////////////////////cars level 3

	obstacleC[12]->setvalue(800, 650, 1);
	//obstacleC[13]->setvalue(1600, 650, 1);
	obstacleC[14]->setvalue(2300, 650, 1);
	obstacleC[15]->setvalue(-2000, 800, 2);
	obstacleC[16]->setvalue(3900, 660, 2);
	obstacleC[17]->setvalue(4900, 590, 3);


	///////////////////////////////////////setting positions of pillars(brikes) for level 1////////////////////////////////////////////////
	pilars pilar[300];

	

	worldObstacles *obstacleP[300];
	
	for (int i = 0; i < 300; i++)
	{
		obstacleP[i] = &pilar[i];
	}
	
	int b1 = 0;
	for (int i = 0; i < 9; i++){
		
			b1 += 32;
		obstacleP[i]->setvalue(1100+b1, 550, 1);
		
	}
	int b2 = 0;
	for (int i = 10; i < 18; i++){

		b2 += 32;
		obstacleP[i]->setvalue(1900 + b2, 550, 1);
	}
	int b3 = 0;
	for (int i = 19; i < 28; i++){

		b3 += 32;
		obstacleP[i]->setvalue(3000 + b3, 550, 1);
	}
	int b4 = 0;
	for (int i = 28; i < 38; i++){

		b4 += 32;
		obstacleP[i]->setvalue(3288 + b4, 400, 1);
	}
	///////////////////////////////////////setting positions of pillars(bricks) for level 2////////////////////////////////////////////////
	int l2b1 = 0;
	
	for (int i = 39; i < 48; i++){

		l2b1 += 32;
		obstacleP[i]->setvalue(450 + l2b1, 620, 1);
	}
	
	int l2b2 = 0;
	for (int i = 49; i < 58; i++){

		l2b2 += 32;
		obstacleP[i]->setvalue(1900 + l2b2, 550, 1);
	}
	int l2b3 = 0;
	for (int i = 59; i < 68; i++){

		l2b3 += 32;
		obstacleP[i]->setvalue(3000 + l2b3, 550, 1);
	}
	int l2b4 = 0;
	for (int i = 78; i < 88; i++){

		obstacleP[i]->setvalue(3288 + l2b4, 400, 1);
		l2b4 += 32;
	}
	obstacleP[89]->setvalue(2600, 550, 1);
	obstacleP[90]->setvalue(2750, 550, 1);
	obstacleP[91]->setvalue(2782, 550, 1);
	int l2b5 = 0;
	for (int i = 92; i < 96; i++){

		obstacleP[i]->setvalue(3660+ l2b5, 300, 1);
		l2b5 += 32;
	}
	int l2b6 = 0;
	for (int i = 97; i < 100; i++){

		obstacleP[i]->setvalue(3850 + l2b6, 450, 1);
		l2b6 += 32;
	}
	drawMulti(97, 105, 32, obstacleP, 20, 450, 1);

	int l2b7 = 0;
	for (int i = 100; i < 104; i++){

		obstacleP[i]->setvalue(4000 + l2b7, 380, 1);
		l2b7 += 32;
	}
	int l2b8 = 0;
	for (int i = 105; i < 108; i++){

		obstacleP[i]->setvalue(4200 + l2b8, 480, 1);
		l2b8 += 32;
	}
	int l2b9 = 0;
	for (int i = 109; i < 115; i++){

		obstacleP[i]->setvalue(5200 + l2b9, 550, 1);
		l2b9 += 32;
	}
	int l2b10 = 0;
	for (int i = 116; i < 120; i++){

		obstacleP[i]->setvalue(6050 + l2b10, 480, 1);
		l2b10 += 32;
	}
	obstacleP[121]->setvalue(5940, 550, 1);
	obstacleP[122]->setvalue(5908, 550, 1);
	int l2b11 = 0;
	for (int i = 123; i < 133; i++){

		obstacleP[i]->setvalue(6200 + l2b11, 400, 1);
		l2b11 += 32;
	}

	////////////////////////////////////////////Level 3 Bricks

	int l3b1 = 0;

	/*for (int i = 92; i < 97; i++){

		l3b1 += 32;
		obstacleP[i]->setvalue(450 + l3b1, 620, 1);
	}*/
	////////////////////////////////////////////man hole poistion  level 2//////////////////////////////////////////////////////////////////////////////////////////
	manHole manH[50];
	worldObstacles *obstacleMH[50];
	for (int i = 0; i < 50; i++)
	{
		obstacleMH[i] = &manH[i];
	}
	obstacleMH[0]->setvalue(7000, 660, 1);
	obstacleMH[1]->setvalue(360, 660, 1);
	int mhl2 = 0;
	for (int i = 2; i < 5; i++){
		obstacleMH[i]->setvalue(2500+mhl2, 660, 1);
		mhl2 += 146;
	}
	obstacleMH[6]->setvalue(3300, 660, 1);
	int mh1l2 = 0;
	for (int i = 7; i < 13; i++){
		obstacleMH[i]->setvalue(3610 + mh1l2, 660, 1);
		mh1l2 += 146;
	}
		int mh2l2 = 0;
	for (int i = 14; i < 19; i++){
		obstacleMH[i]->setvalue(6000 + mh2l2, 660, 1);
		mh2l2 += 146;
	}
	/////////////////////////////////manHoles level 3////////////////////////////////////////////////////////////////////////////////////////////
	obstacleMH[20]->setvalue(1600,660,1);
	//obstacleMH[7]->setvalue(3608, 660, 1);
	////////////////////////////////////////////gansters level 2//////////////////////////////////////////////////////////////////////////////////////////
	gangster[7].setValues(450, 500, 460, 690, 2);
	gangster[8].setValues(1900, 430, 1900, 2140, 2);
	gangster[9].setValues(3000, 430, 3000, 3256, 2);

	///////////////////////gangsters level 3///////////////////////////////////////////////////////////////////////
	gangster[10].setValues(1000, 590, 1000, 1500, 1);	//sets values to enemy
	gangster[11].setValues(1800, 590, 1800, 2200, 1);
	gangster[12].setValues(3000, 600, 3000, 3300, 2);
	//gangster[13].setValues(4050, 600, 4050, 4, 2);
	//gangster[14].setValues(6500, 590, 5400, 5900, 1);
	//gangster[15].setValues(6500, 590, 6000, 6700, 1);
	//gangster[16].setValues(6500, 600, 7600, 8000, 2);
	gangster[17].setValues(530, 500, 530, 690, 1);
	//gangster[18].setValues(1900, 430, 1900, 2140, 2);
	gangster[19].setValues(3070, 430, 3070, 3256, 2);
	//gangster[9].setValues(450, 500, 310, 500, 2);
	////////////////////////////Spikes////////////////////////////////////////////////////////////////////////////////////////////////
	Spikes spikes[100];
	worldObstacles *Obsspikes[100];

	for (int i = 0; i < 100; i++)
	{
		Obsspikes[i] = &spikes[i];
	}

	int l3s1 = 0;

	for (int i = 0; i < 2; i++){

		l3s1 += 32;
		Obsspikes[i]->setvalue(450 + l3s1, 570, 1);
	}
	int l3s2 = 0;
	for (int i = 3; i < 6; i++){

		l3s2 += 32;
		Obsspikes[i]->setvalue(1900 + l3s2, 500, 1);
	}
	int l3s3 = 0;
	for (int i = 7; i < 9; i++){

		l3s3 += 32;
		Obsspikes[i]->setvalue(3000 + l3s3, 500, 1);
	}
	int l3s4 = 0;
	for (int i = 10; i < 12; i++){

		Obsspikes[i]->setvalue(3288 + l3s4, 345, 1);
		l3s4 += 32;
	}
	int l3s5 = 0;
	for (int i = 13; i < 15; i++){

		Obsspikes[i]->setvalue(3480 + l3s4, 430, 2);
		l3s4 += 32;
	}
	int l3s6 = 0;
	for (int i = 16; i < 19; i++){

		Obsspikes[i]->setvalue(3690 + l3s5, 332, 2);
		l3s5 += 32;
	}
	////////////////////////////////////////////Summon Mario//////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////GAME START//////////////////////////////////////////////////////////////////////////////////////////////
	al_start_timer(timer);	// main timer
	al_start_timer(mariotimer);
	al_start_timer(splash);
	al_start_timer(weapontimer);	// mario timer
	al_start_timer(enemyTimer);	// enemy timer
	al_start_timer(luigiTimer);	// luigi timer
	al_get_keyboard_state(&keyState);
	jumpCheck = false;
	//////////////////////////////////////////////////////Songs///////////////////////////////////////////////////
ALLEGRO_SAMPLE *startSound = al_load_sample("1.wav");
	//ALLEGRO_SAMPLE_ID id1;
	ALLEGRO_SAMPLE *gameSong = al_load_sample("Mario Theme Song (thewcoop Trap Remix).wav");
	//ALLEGRO_SAMPLE_ID id2;
	al_reserve_samples(2);
	/////////////////////////////////////////////////////////Start SplashScreen////////////////////////////////////////////////

	
 while (!done)	// splash loop
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);
		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{

			switch (events.keyboard.keycode)
		{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			}
		}

		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}

			if (events.type == ALLEGRO_EVENT_TIMER)
			{
			if (events.timer.source == timer)
			{
				al_play_sample(startSound,1.0,0.0,1.0,ALLEGRO_PLAYMODE_LOOP,0);
				active = true;

				al_get_keyboard_state(&keyState);

				if (al_key_down(&keyState, ALLEGRO_KEY_ENTER))
				{
					done = true;
				}
				draw = true;
			}
			if (draw)
			{
				al_draw_scaled_bitmap(start, 0, 0, al_get_bitmap_width(start), al_get_bitmap_height(start), 0, 0, al_get_bitmap_width(start), al_get_bitmap_height(start), 0);
				al_flip_display();
				draw = false;
			}
		}
	}

	//al_stop_sample(id1);
	al_destroy_sample(startSound);
	bool reset = false;
	/////////////////////////////////////////////////////////End Of Start SplashScreen////////////////////////////////
Line2:

	/////////////////////////////////////////////////////////Reset////////////////////////////////
	if (reset == true)
	{
		while (!done)	// main game loop
		{
			ALLEGRO_EVENT events;
			al_wait_for_event(event_queue, &events);
			if (events.type == ALLEGRO_EVENT_KEY_DOWN)
			{

				switch (events.keyboard.keycode)
				{
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
				}
			}

			else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				done = true;
			}

			if (events.type == ALLEGRO_EVENT_TIMER)
			{
				if (events.timer.source == timer)
				{
					active = true;

					al_get_keyboard_state(&keyState);

					if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
					{
						done = true;
					}
					draw = true;
				}
				if (draw)
				{
					
					al_draw_bitmap(wasted, cameraposition[0], cameraposition[1], NULL);
					al_flip_display();
					reset = false;
					draw = false;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////End Of Reset////////////////////////////////
	done = false;

	level = 1; //The level
	x = 0;


	if (level == 3)
		y = 500;
	else
		y = 600;

	while (!done)	// main game loop
	{
		al_play_sample(gameSong, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, 0);
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);


		
		if (events.type == ALLEGRO_EVENT_KEY_DOWN)
		{

			switch (events.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				return -1;
				break;
			}
		}     
		       
		else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
			return -1;
		}


		if (events.type == ALLEGRO_EVENT_TIMER)
		{


			if (events.timer.source == timer)
			{
				active = true;

				al_get_keyboard_state(&keyState);

				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN))
				{
					hit = false;
					velx = 0;
					y += moveSpeed;
					dir = DOWN;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_SPACE))
				{
					
					hitcheck = true; 
						hit = true;
						velx = 0;
						dir = ATT;
					
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && al_key_down(&keyState, ALLEGRO_KEY_SPACE) && jump == true)
				{
					hit = true;
					vely = -jumpSpeed;
					jump = false;

				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && jump == true)
				{
					vely = -jumpSpeed;
					jump = false;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					hit = false;
					velx = moveSpeed;
					dir = RIGHT;
					check = 1;
					check2 = 1;
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					hit = false;
					velx = -moveSpeed;
					dir = LEFT;
					check = 2;
					check2 = 2;
				}


				else
				{
					if (check == 1 || check == 0)
					{
						hit = false;
						dir = NONE1;

					}
					else
					{
						hit = false;
						dir = NONE2;

					}
					velx = 0;
					active = false;
				}

			}
			else if (events.timer.source == mariotimer)
			{
				
				if (level == 3)
				{
					sourceXd += (float)321;
					sourceXh += (float)321;
				}
				else{
					sourceXd += 73.5;//al_get_bitmap_width(Stand) / 10;
					sourceXh += 73.5;//al_get_bitmap_width(Stand1) / 10;
				}
				if (active)
				{
					if (level == 3)
					{
						sourceXa += (float)al_get_bitmap_width(SuperDuckLeft) / (float)10;
						sourceXb += (float)al_get_bitmap_width(SuperJumpLeft) / (float)10;
						sourceXc += (float)(al_get_bitmap_width(SuperWalkLeft)) / (float)(10);
						
						sourceXe += (float)al_get_bitmap_width(SuperDuckRight) / (float)10;
						sourceXf += (float)al_get_bitmap_width(SuperJumpRight) / (float)10;
						sourceXg += (float)al_get_bitmap_width(SuperWalkRight) / (float)10;
						
						
					}
					else
					{
						sourceXa += 81.5;  //al_get_bitmap_width(Duck) / 10;
						sourceXb += 71.5; //al_get_bitmap_width(Jump) / 10;
						sourceXc += (float)(al_get_bitmap_width(Walk)) / (float)(10);
						
						sourceXe += 81.5;//al_get_bitmap_width(Duck1) / 10;
						sourceXf += 71.5; //al_get_bitmap_width(Jump1) / 10; 
						sourceXg += 107.5;//al_get_bitmap_width(Walk1) / 10;
						
					}
					
				}
				
				if (level == 3)
				{
					if (sourceXa >= al_get_bitmap_width(SuperDuckLeft))
						sourceXa = 0;
					if (sourceXb >= al_get_bitmap_width(SuperJumpLeft))
						sourceXb = 0;
					if (sourceXc >= al_get_bitmap_width(SuperWalkLeft))
						sourceXc = 0;
					if (sourceXd >= al_get_bitmap_width(SuperStandLeft))
						sourceXd = 0;
					if (sourceXe >= al_get_bitmap_width(SuperDuckRight))
						sourceXe = 0;
					if (sourceXf >= al_get_bitmap_width(SuperJumpRight))
						sourceXf = 0;
					if (sourceXg >= al_get_bitmap_width(SuperWalkRight))
						sourceXg = 0;
					if (sourceXh >= al_get_bitmap_width(SuperStandRight))
						sourceXh = 0;
				}
				else
				{
					if (sourceXa >= al_get_bitmap_width(Duck))
						sourceXa = 0;
					if (sourceXb >= al_get_bitmap_width(Jump))
						sourceXb = 0;
					if (sourceXc >= al_get_bitmap_width(Walk))
						sourceXc = 0;
					if (sourceXd >= al_get_bitmap_width(Stand))
						sourceXd = 0;
					if (sourceXe >= al_get_bitmap_width(Duck1))
						sourceXe = 0;
					if (sourceXf >= al_get_bitmap_width(Jump1))
						sourceXf = 0;
					if (sourceXg >= al_get_bitmap_width(Walk1))
						sourceXg = 0;
					if (sourceXh >= al_get_bitmap_width(Stand1))
						sourceXh = 0;
				}
			}
			else if (events.timer.source == weapontimer)
			{
				if (level == 3)
				{
					if (active || hitcheck == true)
					{
						sourceXi += (float)al_get_bitmap_width(SuperAttackLeft)/4.0;
						sourceXj += (float)al_get_bitmap_width(SuperAttackLeft)/4.0;
					}
					if (sourceXi >= al_get_bitmap_width(SuperAttackLeft))
					{
						hitcheck = false;
						sourceXi = 0;
					}

					if (sourceXj >= al_get_bitmap_width(SuperAttackRight))
					{
						hitcheck = false;
						sourceXj = 0;
					}
				}
				else
				{
					if (active || hitcheck == true)
					{
						sourceXi += 467;
						sourceXj += 467;
					}
					if (sourceXi >= al_get_bitmap_width(AttackL))
					{
						hitcheck = false;
						sourceXi = 0;
					}

					if (sourceXj >= al_get_bitmap_width(AttackR))
					{
						hitcheck = false;
						sourceXj = 0;
					}
				}
				
			}
			if (!jump)
				vely += gravity;
			else
				vely = 0;

			x += velx;
			y += vely;
			if (level == 3)
			{
				if (y < 500)
				{
					if (hit == true)
						dir = ATT;
					else
						dir = UP;
				}
				jump = (y >= 500);
				if (jump)
					y = 500;
			}
			else
			{
				if (y < 600)
				{
					if (hit == true)
						dir = ATT;
					else
						dir = UP;
				}
				jump = (y >= 600);
				if (jump)
					y = 600;
			}
		}
		draw = true;
		cameraUpdate(cameraposition, x, y, length / 2, width / 2);//updates the position of camera as mario moves
		al_identity_transform(&CAMERA);                           //transforms the image
		al_translate_transform(&CAMERA, -cameraposition[0], -cameraposition[1]);//translates the camera position
		al_use_transform(&CAMERA);

		
		if (draw)
		{
			if (level == 3)
			{


				switch (dir)
				{
				case 0:
					if (check2 == 1)
					{
						al_draw_bitmap_region(SuperJumpRight, sourceXf, 0, al_get_bitmap_width(SuperJumpRight) / 10, al_get_bitmap_height(SuperJumpRight), x - 20, y, NULL);
						currMario2 = al_create_sub_bitmap(SuperJumpRight, sourceXf, 0, al_get_bitmap_width(SuperJumpRight) / 10, al_get_bitmap_height(SuperJumpRight));
					}
					else
					{
						al_draw_bitmap_region(SuperJumpLeft, sourceXb, 0, al_get_bitmap_width(SuperJumpLeft) / 10, al_get_bitmap_height(SuperJumpLeft), x - 20, y, NULL);
						currMario1 = al_create_sub_bitmap(SuperJumpLeft, sourceXb, 0, al_get_bitmap_width(SuperJumpLeft) / 10, al_get_bitmap_height(SuperJumpLeft));
					}
					break;
				case 1:
					if (check2 == 1)
					{
						al_draw_bitmap_region(SuperDuckRight, sourceXe, 0, al_get_bitmap_width(SuperDuckRight) / 10, al_get_bitmap_height(SuperDuckRight), x - 18, y - 3, NULL);
						currMario2 = al_create_sub_bitmap(SuperDuckRight, sourceXe, 0, al_get_bitmap_width(SuperDuckRight) / 10, al_get_bitmap_height(SuperDuckRight));
					}
					else
					{
						al_draw_bitmap_region(SuperDuckLeft, sourceXa, 0, al_get_bitmap_width(SuperDuckLeft) / 10, al_get_bitmap_height(SuperDuckLeft), x - 18, y - 3, NULL);
						currMario1 = al_create_sub_bitmap(SuperDuckLeft, sourceXa, 0, al_get_bitmap_width(SuperDuckLeft), al_get_bitmap_height(SuperDuckLeft));
					}
					break;
				case 2:
					al_draw_bitmap_region(SuperWalkLeft, sourceXc, 0, al_get_bitmap_width(SuperWalkLeft) / 10, al_get_bitmap_height(SuperWalkLeft), x , y+20, NULL);
					currMario1 = al_create_sub_bitmap(SuperWalkLeft, sourceXc, 0, al_get_bitmap_width(SuperWalkLeft) / 10, al_get_bitmap_height(SuperWalkLeft));
					break;
				case 3:al_draw_bitmap_region(SuperWalkRight, sourceXg, 0, al_get_bitmap_width(SuperWalkRight) / 10, al_get_bitmap_height(SuperWalkRight), x , y+20, NULL);
					currMario2 = al_create_sub_bitmap(SuperWalkRight, sourceXg, 0, al_get_bitmap_width(SuperWalkRight) / 10, al_get_bitmap_height(SuperWalkRight));
					break;
				case 4:al_draw_bitmap_region(SuperStandRight, sourceXh, 0, al_get_bitmap_width(SuperStandRight) / 10, al_get_bitmap_height(SuperStandRight), x, y, NULL);
					currMario2 = al_create_sub_bitmap(SuperStandRight, sourceXh, 0, al_get_bitmap_width(SuperStandRight) / 10, al_get_bitmap_height(SuperStandRight));
					break;
				case 5:
					al_draw_bitmap_region(SuperStandLeft, sourceXd, 0, al_get_bitmap_width(SuperStandLeft) / 10, al_get_bitmap_height(SuperStandLeft), x, y, NULL);
					currMario1 = al_create_sub_bitmap(SuperStandLeft, sourceXd, 0, al_get_bitmap_width(SuperStandLeft) / 10, al_get_bitmap_height(SuperStandLeft));
					break;
				case 6:
					if (check2 == 1)
					{
						al_draw_bitmap_region(SuperAttackRight, sourceXj, 0, al_get_bitmap_width(SuperAttackRight) / 4, al_get_bitmap_height(SuperAttackRight), x - 23, y - 1, NULL);
						currMario2 = al_create_sub_bitmap(SuperAttackRight, sourceXj, 0, al_get_bitmap_width(SuperAttackRight) / 4, al_get_bitmap_height(SuperAttackRight));
					}
					else
					{
						al_draw_bitmap_region(SuperAttackLeft, sourceXi, 0, al_get_bitmap_width(SuperAttackLeft) / 4, al_get_bitmap_height(SuperAttackLeft), x - 565, y - 1, NULL);
						currMario1 = al_create_sub_bitmap(SuperAttackLeft, sourceXi, 0, al_get_bitmap_width(SuperAttackLeft) / 4, al_get_bitmap_height(SuperAttackLeft));
					}
					break;
				}
			}
			else
			{
				switch (dir)
				{
				case 0:
					if (check2 == 1)
					{
						al_draw_bitmap_region(Jump1, sourceXf, 0, al_get_bitmap_width(Jump1) / 10, al_get_bitmap_height(Jump1), x, y, NULL);
						currMario2 = al_create_sub_bitmap(SuperAttackLeft, sourceXf, 0, al_get_bitmap_width(Jump1) / 10, al_get_bitmap_height(SuperAttackLeft));
					}
					else
					{
						al_draw_bitmap_region(Jump, sourceXb, 0, al_get_bitmap_width(Jump) / 10, al_get_bitmap_height(Jump), x, y, NULL);
						currMario1 = al_create_sub_bitmap(SuperAttackLeft, sourceXb, 0, al_get_bitmap_width(Jump) / 10, al_get_bitmap_height(SuperAttackLeft));
					}
					break;
				case 1:
					if (check2 == 1)
					{
						al_draw_bitmap_region(Duck1, sourceXe, 0, al_get_bitmap_width(Duck1) / 10, al_get_bitmap_height(Duck1), x, y + 20, NULL);
						currMario2 = al_create_sub_bitmap(Duck1, sourceXe, 0, al_get_bitmap_width(Duck1) / 10, al_get_bitmap_height(Duck1));
					}
					else
					{
						al_draw_bitmap_region(Duck, sourceXa, 0, al_get_bitmap_width(Duck) / 10, al_get_bitmap_height(Duck), x, y + 20, NULL);
						currMario1 = al_create_sub_bitmap(Duck, sourceXa, 0, al_get_bitmap_width(Duck) / 10, al_get_bitmap_height(Duck));
					}
					break;
				case 2:
					al_draw_bitmap_region(Walk, sourceXc, 0, al_get_bitmap_width(Walk) / 10, al_get_bitmap_height(Walk), x - 20, y, NULL);
					currMario1 = al_create_sub_bitmap(Walk, sourceXc, 0, al_get_bitmap_width(Walk)/10, al_get_bitmap_height(Walk)); 
					break;
				case 3:al_draw_bitmap_region(Walk1, sourceXg, 0, al_get_bitmap_width(Walk1) / 10, al_get_bitmap_height(Walk1), x - 20, y, NULL);
					currMario2 = al_create_sub_bitmap(Walk1, sourceXg, 0, al_get_bitmap_width(Walk1) / 10, al_get_bitmap_height(Walk1)); break;
				case 4:al_draw_bitmap_region(Stand1, sourceXh, 0, al_get_bitmap_width(Stand1) / 10, al_get_bitmap_height(Stand1), x, y, NULL);
					currMario2 = al_create_sub_bitmap(Stand1, sourceXh, 0, al_get_bitmap_width(Stand1) / 10, al_get_bitmap_height(Stand1)); break;
				case 5:
					al_draw_bitmap_region(Stand, sourceXd, 0, al_get_bitmap_width(Stand) / 10, al_get_bitmap_height(Stand), x, y, NULL);
					currMario1 = al_create_sub_bitmap(Stand, sourceXd, 0, al_get_bitmap_width(Stand) / 10, al_get_bitmap_height(Stand)); break;
				case 6:
					if (check2 == 1)
					{
						al_draw_bitmap_region(AttackR, sourceXj, 0, al_get_bitmap_width(AttackR) / 10, al_get_bitmap_height(AttackR), x - 11, y - 19, NULL);
						currMario2 = al_create_sub_bitmap(AttackR, sourceXj, 0, al_get_bitmap_width(AttackR) / 10, al_get_bitmap_height(AttackR));
					}
					else
					{
						al_draw_bitmap_region(AttackL, sourceXi, 0, al_get_bitmap_width(AttackL) / 10, al_get_bitmap_height(AttackL), x - 148, y - 19, NULL);
						currMario1 = al_create_sub_bitmap(AttackL, sourceXi, 0, al_get_bitmap_width(AttackL) / 10, al_get_bitmap_height(AttackL));
					}
					break;
				}
			}
			draw = false;
			al_flip_display();//shows the display window on pc window
			//			al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);
			for (int i = 0; i <= 5; i++)//for loop created to redraw the background according to level lenght
			{
				al_draw_bitmap(imagewindowsky, (length*i), 0, NULL);	// draws sky to window
				al_draw_bitmap(imagewindow, (length*i), 3, NULL);	// draws buildings to window.
			}

		



			if (level == 1)
				//////////////////////////LEVEL 1//////////////////////////////////////////////////////////////////
			{
				enemyMovespeed = 2;

				for (int j = 0; j < 6; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				for (int j = 0; j < 50; j++){
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

				}


				for (int i = 0; i <6/* numOfEnemys*/; i++)
				{
					gangster[i].move(enemyMovespeed);
					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}
				obstacleMH[0]->draw(manhole, manhole, manhole);
			}
			//////////////////////////LEVEL 2//////////////////////////////////////////////////////////////////
			if (level == 2)
			{
				enemyMovespeed = 3;

				for (int j = 6; j < 11; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				for (int j = 39; j < 200; j++){
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

				}
				for (int j = 1; j < 19; j++){
					obstacleMH[j]->draw(manhole, manhole, manhole);
				}


				for (int i = 7; i < 10; i++)
				{
					gangster[i].move(enemyMovespeed);
					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}

				
				//al_draw_bitmap(manhole, 7450, 670, NULL);
			}
			
			if (level == 3)
			{
				enemyMovespeed = 4;

				for (int j = 12; j < 16; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				for (int j = 39; j < 100; j++){
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);
				}
					for (int j = 1; j < 50; j++){
						obstacleMH[j]->draw(manhole, manhole, manhole);
						}
					
					
					for (int j = 0; j < 100; j++)
					{
						Obsspikes[j]->draw(spike, spikeflip, spike);
												
						///////////check for spike collision////////////////////
						
						if (check2 == 1)
						{
							currMario2 = al_create_sub_bitmap(SuperAttackRight, sourceXj, 100, 195, 127);
							//al_draw_bitmap(currMario2, x - 23, y + 100,NULL);
							if (marioObject.spikeCollision(currMario2, spike, x - 23, y + 100, 195, 127, spikes[j].x, spikes[j].y, al_get_bitmap_width(spike), al_get_bitmap_height(spike)))
							{
								reset = true;
								goto Line2;
							}
						}
						else
						{
							currMario1 = al_create_sub_bitmap(SuperAttackLeft, sourceXi + 553, 100, 133, 127);
							//al_draw_bitmap(currMario1, x - 23, y + 100, NULL);
							if (marioObject.spikeCollision(currMario1, spike, x - 23, y + 100, 195, 127, spikes[j].x, spikes[j].y, al_get_bitmap_width(spike), al_get_bitmap_height(spike)))
							{

								reset = true;
								goto Line2;
							}
						}

					}
				
					
				for (int i = 10; i < numOfEnemys; i++)
				{
					gangster[i].move(enemyMovespeed);

					al_lock_bitmap(SuperAttackRight, al_get_bitmap_format(SuperAttackRight), ALLEGRO_LOCK_READONLY);
					al_lock_bitmap(SuperAttackLeft, al_get_bitmap_format(SuperAttackLeft), ALLEGRO_LOCK_READONLY);

					ALLEGRO_BITMAP *currMario;
					
					//////////////////checks if enemy dies////////////////////////
  					if (check2 == 1)
					{
						currMario = al_create_sub_bitmap(SuperAttackRight, sourceXj + 195 , 0, 553, 227);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x + 172, y, al_get_bitmap_width(currMario), 227, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					else
					{
						currMario = al_create_sub_bitmap(SuperAttackLeft, sourceXi, 0, 553, 227);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x - 553, y, al_get_bitmap_width(currMario), 227, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					
					///////////////checks if mario dies////////////////////////
					if (check2 == 1)
					{
						currMario2 = al_create_sub_bitmap(SuperAttackRight, sourceXj, 100, 195, 127);
						//al_draw_bitmap(currMario2, x - 23, y + 100,NULL);
						if (marioObject.marioCollide(x - 23 , y + 100, gangster[i].x, gangster[i].y, al_get_bitmap_width(currMario2), 100, currMario2, punch_gangster,gangster[i].aniWidth,gangster[i].aniHeight) )//|| marioObject.marioCollide(x, y, gangster[i].x, gangster[i].y, al_get_bitmap_width(currMario), 100, currMario1, chain_gangster))
						{
							reset = true;
							goto Line2;
						}
						al_destroy_bitmap(currMario2);
					}
					else
					{
						currMario1 = al_create_sub_bitmap(SuperAttackLeft, sourceXi + 553, 100, 133, 127);
						//al_draw_bitmap(currMario1, x - 23, y + 100, NULL);
						if (marioObject.marioCollide(x, y + 127, gangster[i].x, gangster[i].y, al_get_bitmap_width(currMario1), 100, currMario1, punch_gangster, gangster[i].aniWidth, gangster[i].aniHeight))// || marioObject.marioCollide(x, y, gangster[i].x, gangster[i].y, al_get_bitmap_width(currMario), 100, currMario1, chain_gangster))
						{

							reset = true;
							goto Line2;
						}
						al_destroy_bitmap(currMario1);
					}

					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
					al_destroy_bitmap(currMario);
				}


				luigi.draw(luigiBM, (events.timer.source == luigiTimer), lightning.active);
				lightning.active = luigi.lightning_active();
				lightning.draw(light, (events.timer.source == enemyTimer));
				luigi.drawHealth(luigiHealth);
			}

		}
		
	}
	//al_stop_sample(&id2);

	
	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	
	//al_flip_display();
	
	//al_destroy_font(font);
	al_rest(2.0);//delay
	al_destroy_display(display);
	al_destroy_sample(gameSong);
	al_destroy_bitmap(Jump);
	al_destroy_bitmap(Stand);
	al_destroy_bitmap(Walk);
	al_destroy_bitmap(Duck);
	al_destroy_bitmap(AttackL);
	al_destroy_bitmap(Jump1);
	al_destroy_bitmap(Stand1);
	al_destroy_bitmap(Walk1);
	al_destroy_bitmap(Duck1);
	al_destroy_bitmap(AttackR);
	al_destroy_bitmap(SuperDuckLeft);
	al_destroy_bitmap(SuperStandLeft);
	al_destroy_bitmap(SuperJumpLeft);
	al_destroy_bitmap(SuperWalkLeft);
	
	al_destroy_bitmap(SuperDuckRight);
	al_destroy_bitmap(SuperStandRight);
	al_destroy_bitmap(SuperJumpRight);
	al_destroy_bitmap(SuperWalkRight);
	
	al_destroy_bitmap(imagewindow);
	al_destroy_bitmap(imagewindowsky); 
	al_destroy_bitmap(imagecar);
	al_destroy_bitmap(imagecopcar);
	al_destroy_timer(timer);
	al_destroy_bitmap(smallPillar);
	al_destroy_bitmap(medPillar);
	al_destroy_bitmap(punch_gangster);
	al_destroy_bitmap(chain_gangster);
	al_destroy_bitmap(manhole);
	al_destroy_bitmap(light);
	al_destroy_bitmap(luigiBM);
	al_destroy_timer(luigiTimer);
	al_destroy_bitmap(luigiHealth);
	al_destroy_bitmap(spike);
	al_destroy_bitmap(spikeflip);
	
	return 0;
}