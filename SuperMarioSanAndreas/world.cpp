#include <allegro5/allegro.h>//telling compiler to include allegro 5 files
#include <iostream> //telling compiler to include iostream files
#include <allegro5/allegro_image.h>//telling compiler to include allegro 5 image file
#include <allegro5/allegro_primitives.h>//telling compiler to include allegro 5 primitives
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>	
using namespace std;
#define length 1366 //defining the screen lenght 
#define width 770  //defining the screen width 
#include "Enemies.cpp"
#include "pilars.cpp"
#include "Cars.cpp"
#include "world obstacles.cpp"
#include "manHoles.cpp"
#include "Luigi_lightning.cpp"
#include "Luigi.cpp"
#include "SuperMario.cpp"

void cameraUpdate(float *camerposition, float x, float y, int w, int h){
	camerposition[0] = -(length / 2) + (x + w / 2);				//positioning the camera at midpoint of the screen on the x axis
	if (camerposition[0] < 0)									//check if the position is less then zero and if true then make it equal to zero
		camerposition[0] = 0;
}

 int main(){//main function

	 al_init();


	 bool done = false, draw = false;
	 int x = 0, y = 0, movespeed = 5;
	 int state = NULL;
	 const float FPS = 60.0;
	 const float EFPS = 15.0;
	 const float LFPS = 5.0;
	 enum Direction {/*UP, DOWN, */LEFT, RIGHT};
	 int level;//tells you what level you are currently drawing
	 const int numOfEnemys = 10;					//contains the number of enemies
	 
	// int dir = DOWN;

	ALLEGRO_DISPLAY *display;
	al_set_new_display_flags(ALLEGRO_WINDOWED|ALLEGRO_RESIZABLE);
	display = al_create_display(length, width);
	al_set_window_position(display, 0, 0);

	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	float cameraposition[2] = { 0, 0 };

	ALLEGRO_KEYBOARD_STATE keyState;
	
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();// create pointer for keyboard
	
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //stores the keyboard buttons in a queue to be executed
	
	
	
	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *mariotimer = al_create_timer(1.0 / FPS); //event 1/60 sec, the game will update
	ALLEGRO_TIMER *enemyTimer = al_create_timer(1.0 / EFPS);			//controls the animation of enemies  
	ALLEGRO_TIMER *luigiTimer = al_create_timer(1.0 / LFPS);			//controls the animation of Luigi
	
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(mariotimer));
	al_register_event_source(event_queue, al_get_timer_event_source(enemyTimer));
	al_register_event_source(event_queue, al_get_timer_event_source(luigiTimer));
	ALLEGRO_TRANSFORM CAMERA;

	///////////////////////////////////////////////////////////////////////IMAGE LOADING/////////////////////////////////////////////////////////////

	ALLEGRO_BITMAP *Mario = al_load_bitmap("Try1.png");
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
	ALLEGRO_BITMAP *light = al_load_bitmap("Lightning sprite.png");
	ALLEGRO_BITMAP *luigiBM = al_load_bitmap("Luigi.png");

	///////////////////////////////////////////////////CALLING CLASSES/////////////////////////////////////////////////////////////////////////////

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

	
   
	///////////////////////setting values for the position of cars//////////////////////////////////////////
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
	obstacleC[9]->setvalue(-2000, 800, 2);
	obstacleC[10]->setvalue(3900, 660, 2);
	obstacleC[11]->setvalue(4900, 590, 3);
	/*obstacle[12]->setvalue(, 590, 3);
	obstacle[13]->setvalue(4900, 590, 3); 
	obstacle[14]->setvalue(4900, 590, 3);*/

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
	///////////////////////////////////////setting positions of pillars(brikes) for level 1////////////////////////////////////////////////
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

		l2b4 += 32;
		obstacleP[i]->setvalue(3288 + l2b4, 400, 1);
	}
	obstacleP[89]->setvalue(2600, 550, 1);
	obstacleP[90]->setvalue(2750, 550, 1);
	obstacleP[91]->setvalue(2782, 550, 1);
	////////////////////////////////////////////man hole poistion  level 2//////////////////////////////////////////////////////////////////////////////////////////
	manHole manH[15];
	worldObstacles *obstacleMH[15];
	for (int i = 0; i < 15; i++)
	{
		obstacleMH[i] = &manH[i];
	}
	obstacleMH[1]->setvalue(360, 660, 1);
	int by = 0;
	for (int i = 2; i < 5; i++){
		obstacleMH[i]->setvalue(2500+by, 660, 1);
		by += 146;
	}
	////////////////////////////////////////////gansters level 2//////////////////////////////////////////////////////////////////////////////////////////
	gangster[6].setValues(450, 500, 450, 690, 2);
	gangster[7].setValues(1900, 430, 1900, 2140, 2);
	gangster[8].setValues(3000, 430, 3000, 3256, 2);
	////////////////////////////////////////////Summon Mario//////////////////////////////////////////////////////////////////////////////////////////////
	SuperMario newMario(10, 400);

	////////////////////////////////////////////GAME START//////////////////////////////////////////////////////////////////////////////////////////////
	al_start_timer(timer);	// main timer
	al_start_timer(mariotimer);	// mario timer
	al_start_timer(enemyTimer);	// enemy timer
	al_start_timer(luigiTimer);	// luigi timer

	while (!done)	// main game loop
	{
		ALLEGRO_EVENT events;
		al_wait_for_event(event_queue, &events);

		newMario.startMovement(display, done, events, keyState, Mario);
		draw = true;
		cameraUpdate(cameraposition, x, y, length / 2, width / 2);//updates the position of camera as mario moves
		al_identity_transform(&CAMERA);                           //transforms the image
		al_translate_transform(&CAMERA, -cameraposition[0], -cameraposition[1]);//translates the camera position
		al_use_transform(&CAMERA);

		for (int i = 0; i < numOfEnemys; i++)
		{
			gangster[i].move(movespeed / 2);
		}



		if (draw)
		{

			newMario.drawMario(draw, Mario);
			draw = false;
			al_flip_display();//shows the display window on pc window
			//			al_draw_bitmap(imagewindowsky,/* 1*/x + (length*i), 2, NULL);
			for (int i = 0; i <= 5; i++)//for loop created to redraw the background according to level lenght
			{
				al_draw_bitmap(imagewindowsky, (length*i), 0, NULL);	// draws sky to window
				al_draw_bitmap(imagewindow, (length*i), 3, NULL);	// draws buildings to window.
			}

			level = 2;
			if (level == 1)
				//////////////////////////LEVEL 1//////////////////////////////////////////////////////////////////
			{

				for (int j = 0; j < 6; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				for (int j = 0; j < 50; j++){
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

				}


				for (int i = 0; i < numOfEnemys; i++)
				{
					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}
				obstacleMH[0]->draw(manhole, manhole, manhole);
			}
			//////////////////////////LEVEL 2//////////////////////////////////////////////////////////////////
			if (level == 2){
				for (int j = 6; j < 11; j++){
					obstacleC[j]->draw(imagecar, imagecopcar, imagebus);
				}
				for (int j = 39; j < 100; j++){
					obstacleP[j]->draw(smallPillar, medPillar, medPillar);

				}
				for (int j = 1; j < 15; j++){
					obstacleMH[j]->draw(manhole, manhole, manhole);
				}


				for (int i = 0; i < numOfEnemys; i++)
				{
					gangster[i].draw(punch_gangster, chain_gangster, (events.timer.source == enemyTimer));	// draw method from Enemies class
				}

				luigi.draw(luigiBM, (events.timer.source == luigiTimer), lightning.active);
				lightning.active = luigi.lightning_active();
				lightning.draw(light, (events.timer.source == enemyTimer));
				//al_draw_bitmap(manhole, 7450, 670, NULL);
			}
		}


	}
	

	
	//al_init_font_addon();
	//al_init_ttf_addon();

	//ALLEGRO_FONT *font = al_load_font("emulogic.ttf", 20, NULL);
	
	//al_flip_display();
	
	//al_destroy_font(font);
	al_rest(2.0);//delay
	al_destroy_display(display);
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
	
	return 0;
}