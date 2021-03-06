#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>	
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
#include <string>
#include <sstream>

using namespace std;

void cameraUpdate(float *camerposition, float x, float y, int w, int h){
	camerposition[0] = -(length / 2) + (x + w / 2);				//positioning the camera at midpoint of the screen on the x axis
	if (camerposition[0] < 0)									//check if the position is less then zero and if true then make it equal to zero
		camerposition[0] = 0;
}

int top, bot, lef, righ;


 int main(){//main function

	 al_init();
	 int delay = 0;
	 bool hit = false;
	 bool hitcheck = false;
	 bool newlevel = false;
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
	 float jumpSpeed = 10;
	 
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
	 const float HFPS = 10.0;		//controls hit count for luigi
	 const float MFPS = 8.0;
	 const float WFPS = 9.0;
	 enum Direction {UP, DOWN, LEFT, RIGHT, NONE1, NONE2, ATT};
	 int level;//tells you what level you are currently drawing
	 const int numOfEnemys = 24;					//contains the number of enemies
	 bool jumpCheck;
	 int check2;
	// int dir = DOWN;

	 ////////////player variables////////////
	 int score = 0;
	 int prevX = 0;
	 int lives = 5;

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
	ALLEGRO_TIMER *hitTime = al_create_timer(1.0 / HFPS);

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
	al_register_event_source(event_queue, al_get_timer_event_source(hitTime));
	ALLEGRO_TRANSFORM CAMERA;

	///////////////////////////////////////////////////////////////////////Splash Screen Loading/////////////////////////////////////////////////////////////
	ALLEGRO_BITMAP *start = al_load_bitmap("start.png");
	ALLEGRO_BITMAP *wasted = al_load_bitmap("wasted.png");
	ALLEGRO_BITMAP *level1 = al_load_bitmap("Level1.png");
	ALLEGRO_BITMAP *level2 = al_load_bitmap("Level2.png");
	ALLEGRO_BITMAP *level3 = al_load_bitmap("Level3.png");
	ALLEGRO_BITMAP *victory = al_load_bitmap("victory.png");

	///////////////////////////////////////////////////////////////////////Image Loading/////////////////////////////////////////////////////////////////////
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

	ALLEGRO_BITMAP *light = al_load_bitmap("Lightning sprite1.png");
	ALLEGRO_BITMAP *luigiBM = al_load_bitmap("Luigi.png");
	ALLEGRO_BITMAP *luigiHealth = al_load_bitmap("Luigi_health_bar.png");

	ALLEGRO_BITMAP *endflag = al_load_bitmap("endflag.png");
	ALLEGRO_BITMAP *castle = al_load_bitmap("castle.png");
	ALLEGRO_BITMAP *princess = al_load_bitmap("princess.png");

	ALLEGRO_BITMAP *currMario1;
	ALLEGRO_BITMAP *currMario2;

	al_init_font_addon();
	al_init_ttf_addon();

	ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 25, NULL);

	//////////////////////////////////AUDIO/////////////////////////////////////////////////

	al_reserve_samples(6);

	ALLEGRO_SAMPLE *startSound = al_load_sample("1.wav");
	ALLEGRO_SAMPLE_INSTANCE *startInstance = al_create_sample_instance(startSound);
	al_set_sample_instance_playmode(startInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(startInstance, al_get_default_mixer());

	ALLEGRO_SAMPLE *gameSong = al_load_sample("Mario Theme Song (thewcoop Trap Remix).wav");
	ALLEGRO_SAMPLE_INSTANCE *gameInstance = al_create_sample_instance(gameSong);
	al_set_sample_instance_playmode(gameInstance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(gameInstance, al_get_default_mixer());

	ALLEGRO_SAMPLE *jumpsound = al_load_sample("jump.wav");
	ALLEGRO_SAMPLE *hammerthrow = al_load_sample("hammer.wav");
	ALLEGRO_SAMPLE *fire = al_load_sample("fire.wav");
	ALLEGRO_SAMPLE *dying = al_load_sample("Dying.wav");
	
	///////////////////////////CALLING CLASSES////////////////////////////////////////////

	SuperMario marioObject;

	Enemies gangster[numOfEnemys];	//creates 1 object of enemies class

	Cars car[12];
	worldObstacles *obstacleC[12];
	for (int i = 0; i < 12; i++)
	{
		obstacleC[i] = &car[i];
	}

	pilars pilar[142];
	worldObstacles *obstacleP[142];
	for (int i = 0; i < 142; i++)
	{
		obstacleP[i] = &pilar[i];
	}

	manHole manH[50];
	worldObstacles *obstacleMH[50];
	for (int i = 0; i < 50; i++)
	{
		obstacleMH[i] = &manH[i];
	}

	Spikes spikes[100];
	worldObstacles *Obsspikes[100];
	for (int i = 0; i < 100; i++)
	{
		Obsspikes[i] = &spikes[i];
	}
	
	Luigi luigi;						//Luigi positioned at end with lightning 
	luigi.x = 7500;
	luigi.y = 550;

	Luigi_lightning lightning;						
	lightning.x = luigi.x+10;
	lightning.y = luigi.y+40;

	
   
	///////////////////////SETTING CAR POSITIONS//////////////////////////////////////////

	/////////////////////////////LEVEL 1//////////////////////////////////////////////////

	obstacleC[0]->setvalue(800, 620, 1);
	obstacleC[1]->setvalue(1600, 620, 1);
	obstacleC[2]->setvalue(2300, 620, 1);
	obstacleC[3]->setvalue(2800, 630, 2);
	obstacleC[4]->setvalue(3900, 630, 2);
	obstacleC[5]->setvalue(4900, 560, 3);

	/////////////////////////////LEVEL 2//////////////////////////////////////////////////

	obstacleC[6]->setvalue(800, 620, 1);
	obstacleC[7]->setvalue(1600, 620, 1);
	obstacleC[8]->setvalue(2300, 620, 1);

	/////////////////////////////LEVEL 3//////////////////////////////////////////////////
	
	obstacleC[9]->setvalue(800, 620, 1);
	obstacleC[10]->setvalue(2300, 620, 1);
	obstacleC[11]->setvalue(4900, 560, 3);
	
	///////////////////////SETTING ENEMY POSITIONS//////////////////////////////////////////

	/////////////////////////////////LEVEL 1///////////////////////////////////////////////

	gangster[0].setValues(1000, 590, 1000, 1500, 1);	//sets values to enemy
	gangster[1].setValues(1800, 590, 1800, 2200, 1);
	gangster[2].setValues(3000, 600, 3000, 3800, 2);
	gangster[3].setValues(4050, 600, 4080, 4800, 2);
	gangster[4].setValues(6500, 590, 5400, 5900, 1);
	gangster[5].setValues(6500, 590, 6000, 6700, 1);
	gangster[6].setValues(6500, 600, 7600, 8000, 2);

	/////////////////////////////////LEVEL 2///////////////////////////////////////////////

	gangster[7].setValues(1000, 590, 1000, 1500, 1);	//sets values to enemy
	gangster[8].setValues(1800, 590, 1800, 2200, 1);
	gangster[10].setValues(4050, 600, 4450, 5200, 2);
	gangster[11].setValues(6500, 590, 5400, 5900, 1);
	gangster[12].setValues(6500, 590, 6800, 7500, 1);
	gangster[13].setValues(6500, 600, 7600, 8000, 2);
	gangster[14].setValues(450, 500, 460, 690, 2);
	gangster[15].setValues(1900, 430, 1900, 2140, 2);
	gangster[16].setValues(3000, 430, 3000, 3256, 2);

	/////////////////////////////////LEVEL 3///////////////////////////////////////////////

	gangster[17].setValues(1000, 590, 1000, 1500, 1);	//sets values to enemy
	gangster[18].setValues(1800, 590, 1800, 2200, 1);
	gangster[19].setValues(3000, 600, 2900, 3200, 2);
	gangster[20].setValues(3000, 600, 4400, 4780, 2);
	gangster[21].setValues(6500, 590, 5400, 5900, 1);
	gangster[22].setValues(530, 503, 530, 690, 1);
	gangster[23].setValues(3070, 430, 3070, 3256, 2);
	
	///////////////////////////////////////SETTING BRICK POSITIONS//////////////////////////

	/////////////////////////////////LEVEL 1///////////////////////////////////////////////

	int b1 = 0;
	for (int i = 0; i < 9; i++){

		b1 += 32;
		obstacleP[i]->setvalue(1100 + b1, 550, 1);

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

	/////////////////////////////////LEVEL 2 & 3///////////////////////////////////////////////

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

		obstacleP[i]->setvalue(3660 + l2b5, 300, 1);
		l2b5 += 32;
	}

	int l2b6 = 0;
	for (int i = 97; i < 100; i++){

		obstacleP[i]->setvalue(3850 + l2b6, 450, 1);
		l2b6 += 32;
	}

	int l2b7 = 0;
	for (int i = 100; i < 106; i++){

		obstacleP[i]->setvalue(4000 + l2b7, 380, 1);
		l2b7 += 32;
	}

	int l2b8 = 0;
	for (int i = 107; i < 111; i++){

		obstacleP[i]->setvalue(4275 + l2b8, 480, 1);
		l2b8 += 32;
	}

	int l2b9 = 0;
	for (int i = 112; i < 118; i++){

		obstacleP[i]->setvalue(5200 + l2b9, 472, 1);
		l2b9 += 32;
	}

	int l2b10 = 0;
	for (int i = 119; i < 127; i++){

		obstacleP[i]->setvalue(6050 + l2b10, 480, 1);
		l2b10 += 32;
	}

	obstacleP[128]->setvalue(5940, 550, 1);
	obstacleP[129]->setvalue(5908, 550, 1);

	int l2b11 = 0;
	for (int i = 130; i < 141; i++){

		obstacleP[i]->setvalue(6250 + l2b11, 350, 1);
		l2b11 += 32;
	}
	
	
	///////////////////////////SETTING MANHOLE POSITIONS///////////////////////////////////

	/////////////////////////////////LEVEL 2///////////////////////////////////////////////

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

	/////////////////////////////////LEVEL 3///////////////////////////////////////////////
	obstacleMH[20]->setvalue(1600,660,1);

	////////////////////////////SETTING SPIKE POSITIONS///////////////////////////////////
	
	int l3s1 = 0;
	for (int i = 0; i < 2; i++){

		l3s1 += 32;
		Obsspikes[i]->setvalue(450 + l3s1, 568, 1);
	}

	int l3s2 = 0;
	for (int i = 3; i < 6; i++){

		l3s2 += 32;
		Obsspikes[i]->setvalue(1900 + l3s2, 498, 1);
	}

	int l3s3 = 0;
	for (int i = 7; i < 9; i++){

		l3s3 += 32;
		Obsspikes[i]->setvalue(3000 + l3s3, 498, 1);
	}

	int l3s4 = 0;
	for (int i = 10; i < 12; i++){

		Obsspikes[i]->setvalue(3288 + l3s4, 349, 1);
		l3s4 += 32;
	}

	int l3s5 = 0;
	for (int i = 13; i < 15; i++){

		Obsspikes[i]->setvalue(3480 + l3s4, 428, 2);
		l3s4 += 32;
	}

	int l3s6 = 0;
	for (int i = 16; i < 19; i++){

		Obsspikes[i]->setvalue(3690 + l3s5, 327, 2);
		l3s5 += 32;
	}

	int l3s7 = 0;
	for (int i = 20; i < 23; i++){

		Obsspikes[i]->setvalue(3850 + l3s7, 397, 1);
		l3s7 += 32;
	}
	
	Obsspikes[24]->setvalue(4000, 328, 1);
	Obsspikes[25]->setvalue(4160, 328, 1);
	Obsspikes[26]->setvalue(4275, 428, 1);

	int l3s8 = 0;
	for (int i = 27; i < 33; i++){

		Obsspikes[i]->setvalue(5200 + l3s8, 500, 2);
		l3s8 += 32;
	}

	int l3s9 = 0;
	for (int i = 34; i < 36; i++){
		Obsspikes[i]->setvalue(5328+l3s9, 420, 1);
		l3s9 += 32;
	}

	int l3s10 = 0;
	for (int i = 37; i < 42; i++){

		Obsspikes[i]->setvalue(6143 + l3s10, 427, 1);
		l3s10 += 32;
	}
	
	int l3s11 = 0;
	for (int i = 43; i < 45; i++){

		Obsspikes[i]->setvalue(6532 + l3s11, 298, 1);
		l3s11 += 32;
	}

	Obsspikes[46]->setvalue(6340, 298, 1);
	
	/////////////////////////////GAME START//////////////////////////////////////////////

	al_start_timer(timer);	// main timeR
	al_start_timer(mariotimer);
	al_start_timer(splash);
	al_start_timer(weapontimer);	// mario timer
	al_start_timer(enemyTimer);	// enemy timer
	al_start_timer(luigiTimer);	// luigi timer
	al_start_timer(hitTime);
	al_get_keyboard_state(&keyState);
	jumpCheck = false;
	
	//////////////////////////////Start SplashScreen///////////////////////////////////

	
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
				al_play_sample_instance(startInstance);
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

	
	al_destroy_sample(startSound);
	al_destroy_sample_instance(startInstance);
	bool reset = false;
	/////////////////////////////////////////////////////////End Of Start SplashScreen////////////////////////////////
	level = 1; //The level
	int ctrl = 0; 

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
					if (ctrl == 0)
 						al_draw_bitmap(wasted, cameraposition[0], cameraposition[1], NULL);
					else if (ctrl == 1)
					{
						prevX = 0;
						al_draw_bitmap(level1, cameraposition[0], cameraposition[1], NULL);
					}
					else if (ctrl == 2)
					{
						prevX = 0;
						al_draw_bitmap(level2, cameraposition[0], cameraposition[1], NULL);
					}
					else if (ctrl == 3)
					{
						prevX = 0;
						al_draw_bitmap(level3, cameraposition[0], cameraposition[1], NULL);
					}
					else if (ctrl == 4)
					{
						prevX = 0;
						al_draw_bitmap(victory, cameraposition[0], cameraposition[1], NULL);
					}
					al_flip_display();
					reset = false;
					draw = false;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////End Of Reset////////////////////////////////
	

	///////////////////////////////////////////END SPLASH//////////////////////////////////////////
	done = false;

	
	x = 0;

	if (level == 3)
		y = 500;
	else
		y = 600;

	while (!done)	// main game loop
	{
		al_play_sample_instance(gameInstance);
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
						if (level == 3)
						{
							al_play_sample(fire, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}
						else{
							al_play_sample(hammerthrow, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						}

					
				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && al_key_down(&keyState, ALLEGRO_KEY_SPACE) && jump == true)
				{
					hit = true;
					vely = -jumpSpeed;
					jump = false;
					if (level == 3)
					{
						al_play_sample(fire, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						al_play_sample(jumpsound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}
					else{
						al_play_sample(hammerthrow, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
						al_play_sample(jumpsound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					}

				}
				else if (al_key_down(&keyState, ALLEGRO_KEY_UP) && jump == true)
				{
					vely = -jumpSpeed;
					jump = false;
					al_play_sample(jumpsound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
					
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
			{
				vely += gravity;
				
			}
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
			for (int i = 0; i <= 6; i++)//for loop created to redraw the background according to level lenght
			{
				al_draw_bitmap(imagewindowsky, (length*i), 0, NULL);	// draws sky to window
				al_draw_bitmap(imagewindow, (length*i), 3, NULL);	// draws buildings to window.
			}

		
			if (x > prevX)
			{
				score += (x - prevX);
				prevX = x;
			}

			al_draw_textf(font, al_map_rgb(0, 0, 0), x + length / 4, 0, ALLEGRO_ALIGN_CENTRE, "SCORE : %d", score);

			if (level == 1)
				//////////////////////////LEVEL 1//////////////////////////////////////////////////////////////////
			{
				enemyMovespeed = 2;

				for (int j = 0; j < 6; j++)
				{
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}

				for (int j = 0; j < 39; j++)
				{
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

					//////check block/pillar collision///////////////
					
					bool coll = false;
					if ((x - 20 > pilar[j].x && x - 20 < pilar[j].x + 32) || (x + 87 > pilar[j].x  &&  x + 87 < pilar[j].x + 32))  //means mario is either above or below block
					{
						
						if (y > pilar[j].y && y < pilar[j].y + 32)		//stop mario jump when head hit bottom of block
						{
							vely = gravity;
							y = pilar[j].y + 32;
							coll = true;
						}

						if (y + 123 > pilar[j].y && y + 123 < pilar[j].y + 32)	//allows mario to land on block
						{
							y = pilar[j].y - 123;
							jump = true;
							vely = 0;
							coll = true;
				}

					}
					if (!coll)
					{
						if ((pilar[j].y > y && pilar[j].y < y + 123) || (pilar[j].y + 32 > y && pilar[j].y + 32 < y + 123)) //checks if mario is next to block on the left or right
						{

							if (x - 20 > pilar[j].x && x - 20 < pilar[j].x + 32)		//hitting block on the right side
							{
								x = pilar[j].x + 32;
							}
							if (x + 87 > pilar[j].x  &&  x + 87 < pilar[j].x + 32)	//hitting block on the left side
							{
								x = pilar[j].x - 123;
							}
						}
					}
				}


				for (int i = 0; i <6; i++)
				{
					gangster[i].move(enemyMovespeed);

					////////////////check if kill enemies//////////////////////
					ALLEGRO_BITMAP *currMario;
					al_lock_bitmap(AttackR, al_get_bitmap_format(AttackR), ALLEGRO_LOCK_READONLY);
					al_lock_bitmap(AttackL, al_get_bitmap_format(AttackL), ALLEGRO_LOCK_READONLY);

					if (check2 == 1)
					{
						currMario = al_create_sub_bitmap(AttackR, sourceXj + 100, 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x + 89, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					else
					{
						currMario = al_create_sub_bitmap(AttackL, sourceXi, 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x - 148, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					al_destroy_bitmap(currMario);

					///////////checks if mario dies by enemy///////////////
					if (marioObject.marioCollide(x - 20, y, gangster[i].x, gangster[i].y, al_get_bitmap_width(Walk) / 10, 123, Walk, punch_gangster, gangster[i].aniWidth, gangster[i].aniHeight))
					{
						reset = true;
						ctrl = 0;
						goto Line2;
					}


					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}

				obstacleMH[0]->draw(manhole, manhole, manhole);
				if (marioObject.fall_in_manhole(x + 20, y, manH[0].x, manH[0].y, al_get_bitmap_width(manhole)))
				{
					reset = true;
					ctrl = 0;
					goto Line2;
				}

				if (x < 0)			//prevents mario from running away
					x = 0;

				al_draw_bitmap(endflag, 8140, 0, NULL);
				al_draw_bitmap(castle, 8250, 0, NULL);

				if (x > 8160)			//moves to level 2
				{
					level = 2;
					reset = true;
					ctrl = 2;
					goto Line2;


				}
			}






			//////////////////////////LEVEL 2//////////////////////////////////////////////////////////////////
			if (level == 2)
			{
				enemyMovespeed = 3;

				for (int j = 6; j < 9; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}

				for (int j = 39; j < 142; j++)
				{
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

					////////block collision//////////////////
					bool coll = false;
					if ((x - 20 > pilar[j].x && x - 20 < pilar[j].x + 32) || (x + 87 > pilar[j].x  &&  x + 87 < pilar[j].x + 75))  //means mario is either above or below block
					{

						if (y > pilar[j].y && y < pilar[j].y + 32)		//stop mario jump when head hit bottom of block
						{
							vely = gravity;
							y = pilar[j].y + 32;
							coll = true;
				}

						//al_draw_bitmap(smallPillar, x - 20, y + 123, NULL);
						if (y + 123 > pilar[j].y && y + 123 < pilar[j].y + 32)	//allows mario to land on block
						{
							y = pilar[j].y - 123;
							jump = true;
							vely = 0;
							coll = true;
						}

					}
					if (!coll)
					{
						if ((pilar[j].y > y && pilar[j].y < y + 123) || (pilar[j].y + 32 > y && pilar[j].y + 32 < y + 123)) //checks if mario is next to block on the left or right
						{

							if (x - 20 > pilar[j].x && x - 20 < pilar[j].x + 32)		//hitting block on the right side
							{
								x = pilar[j].x + 32;
							}
							if (x + 87 > pilar[j].x  &&  x + 87 < pilar[j].x + 32)	//hitting block on the left side
							{
								x = pilar[j].x - 123;
							}
						}
					}

				}


				for (int j = 1; j < 19; j++)
				{
					obstacleMH[j]->draw(manhole, manhole, manhole);

					/////check manhole collision
					if (marioObject.fall_in_manhole(x + 20, y, manH[j].x, manH[j].y, al_get_bitmap_width(manhole)))
					{
						reset = true;
						ctrl = 0;

						goto Line2;
				}
				}


				for (int i = 7; i < 17; i++)
				{
					gangster[i].move(enemyMovespeed);
					
					////////////////kill enemies//////////////////////
					ALLEGRO_BITMAP *currMario;
					al_lock_bitmap(AttackR, al_get_bitmap_format(AttackR), ALLEGRO_LOCK_READONLY);
					al_lock_bitmap(AttackL, al_get_bitmap_format(AttackL), ALLEGRO_LOCK_READONLY);

					if (check2 == 1)
					{
						currMario = al_create_sub_bitmap(AttackR, sourceXj + 100, 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x + 89, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					else
					{
						currMario = al_create_sub_bitmap(AttackL, sourceXi, 0, 133, 140);	//get current animation of mario
						gangster[i].getHitWithHammer(punch_gangster, chain_gangster, currMario, x - 148, y, al_get_bitmap_width(currMario), 140, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
					}
					al_destroy_bitmap(currMario);

					///////mario gets killed//////////
					if (marioObject.marioCollide(x - 20, y, gangster[i].x, gangster[i].y, al_get_bitmap_width(Walk) / 10, 123, Walk, punch_gangster, gangster[i].aniWidth, gangster[i].aniHeight))
					{
						reset = true;
						ctrl = 0;
						goto Line2;
					}

					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}

				
				//al_draw_bitmap(manhole, 7450, 670, NULL);

				if (x < 0)			//prevents mario from running away
					x = 0;

				al_draw_bitmap(endflag, 8140, 0, NULL);
				al_draw_bitmap(castle, 8250, 0, NULL);
				if (x > 8160)			//moves to level 2
				{
					level = 3;
					reset = true;
					ctrl = 3;

					goto Line2;


				}
			}
			

			////////////////////////level 3//////////////////////

			
			if (level == 3)
			{
				enemyMovespeed = 4;

				for (int j = 9; j < 12; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				
				for (int j = 39; j < 142; j++)
				{
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

					////////block collision//////////////////
					bool coll = false;
					if ((pilar[j].x > x + 36 && pilar[j].x < x + 135) || (pilar[j].x + 32 > x + 36 && pilar[j].x + 32 < x + 135))  //means mario is either above or below block
					{

						if (y + 100 > pilar[j].y && y + 100 < pilar[j].y + 32)		//stop mario jump when head hit bottom of block
						{
							vely = gravity;
							y = pilar[j].y + 32 - 100;
							coll = true;
						}

						//al_draw_bitmap(smallPillar, x + 36, y + 100, NULL);
						if (y + 224 > pilar[j].y && y + 224 < pilar[j].y + 32)	//allows mario to land on block
						{
							y = pilar[j].y - 224;
							jump = true;
							vely = 0;
							coll = true;
						}

					}
					if (!coll)
					{
						if ((pilar[j].y > y + 100 && pilar[j].y < y + 224) || (pilar[j].y + 32 > y + 100 && pilar[j].y + 32 < y + 224)) //checks if mario is next to block on the left or right
						{

							if (pilar[j].x + 32 > x + 36 && pilar[j].x + 32 < x + 135)		//hitting block on the right side
							{
								x = pilar[j].x + 32;
				}
							if (pilar[j].x > x + 36 && pilar[j].x < x + 135)	//hitting block on the left side
							{
								x = pilar[j].x - 99;
							}
						}
					}



				}
					for (int j = 1; j < 50; j++)
					{
						obstacleMH[j]->draw(manhole, manhole, manhole);
					
						///////////check for manhole collision////////////////////
						
						//al_draw_bitmap(manhole, x + 85, 400, NULL);		used for testing purposes
						if (marioObject.fall_in_manhole(x + 85, y + 100, manH[j].x, manH[j].y, al_get_bitmap_width(manhole)))
						{
							reset = true;
							goto Line2;
						}		
					
					}
					
					
					for (int j = 0; j < 100; j++)
					{
						Obsspikes[j]->draw(spike, spikeflip, spike);
												
						///////////check for spike collision////////////////////
						
						if (check2 == 1)
						{
							currMario2 = al_create_sub_bitmap(SuperAttackRight, sourceXj + 50, 100, 83, 127);
							//al_draw_bitmap(currMario2, x + 32 , y + 100,NULL);
							if (marioObject.spikeCollision(currMario2, spike, x + 32, y + 100, 105, 127, spikes[j].x, spikes[j].y, al_get_bitmap_width(spike), al_get_bitmap_height(spike)))
							{
								reset = true;
								ctrl = 0;
								goto Line2;
							}
						}
						else
						{
							currMario1 = al_create_sub_bitmap(SuperAttackLeft, sourceXi + 603, 100, 83, 127);
							//al_draw_bitmap(currMario1, x + 32, y + 100, NULL);
							if (marioObject.spikeCollision(currMario1, spike, x + 32, y + 100, 105, 127, spikes[j].x, spikes[j].y, al_get_bitmap_width(spike), al_get_bitmap_height(spike)))
							{

								reset = true;
								ctrl = 0;
								goto Line2;
							}
					}
				
					}
					
					
				for (int i = 17; i < numOfEnemys; i++)
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
							ctrl = 0;
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
							ctrl = 0;
							goto Line2;
						}
						al_destroy_bitmap(currMario1);
					}

					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
					al_destroy_bitmap(currMario);
				}

				luigi.draw(luigiBM, (events.timer.source == luigiTimer), lightning.active);
				lightning.alive = luigi.alive;
				lightning.active = luigi.lightning_active();
				lightning.draw(light, (events.timer.source == enemyTimer));
				luigi.drawHealth(luigiHealth);

				///check if Mario struck/////////
				if (marioObject.struck(x+100, y, lightning.x - lightning.sourceX[lightning.i],648, lightning.active,luigi.y - 100))
				{
					reset = true;
					ctrl = 0;
					goto Line2;
				}
					
				////////////////check if Luigi dies//////////////////////////////
				ALLEGRO_BITMAP *currMario;
				al_lock_bitmap(SuperAttackRight, al_get_bitmap_format(SuperAttackRight), ALLEGRO_LOCK_READONLY);
				al_lock_bitmap(SuperAttackLeft, al_get_bitmap_format(SuperAttackLeft), ALLEGRO_LOCK_READONLY);

				if (check2 == 1)
				{
					currMario = al_create_sub_bitmap(SuperAttackRight, sourceXj + 195, 0, 553, 227);	//get current animation of mario
					al_lock_bitmap(currMario, al_get_bitmap_format(currMario), ALLEGRO_LOCK_READONLY);
					luigi.getShot(luigiBM, currMario, x + 172, y, al_get_bitmap_width(currMario), 227, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
				}
				else
				{
					currMario = al_create_sub_bitmap(SuperAttackLeft, sourceXi, 0, 553, 227);	//get current animation of mario
					al_lock_bitmap(currMario, al_get_bitmap_format(currMario), ALLEGRO_LOCK_READONLY);
					luigi.getShot(luigiBM, currMario, x - 553, y, al_get_bitmap_width(currMario), 227, hit);	//checks if enemy gets hit with hammer, if true, enemy dies
				}



				al_draw_bitmap(princess, 8200, 0, NULL);

				if (x > 8160)			//won game
				{
						if (luigi.alive) //doesnt allow player to advance without killing luigi
							x = 0;
						else
						{
						level = 4;
						reset = true;
						ctrl = 4;
						goto Line2;
						}
				}
			}

			if (level == 4)
				goto line4;
		}


		
	}
	//al_flip_display();
	
line4:
	
	al_destroy_font(font);
	al_destroy_display(display);
	al_destroy_sample(gameSong);
	al_destroy_sample_instance(gameInstance);
	al_destroy_sample(jumpsound);
	al_destroy_sample(hammerthrow);
	al_destroy_sample(fire);
	al_destroy_sample(dying);
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
	al_destroy_bitmap(endflag);
	al_destroy_bitmap(castle);
	al_destroy_bitmap(princess);
	return 0;
}

