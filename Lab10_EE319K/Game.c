//game stuff!
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "ADC.h"
#include "ST7735.h"
#include "Images.h"
#include "Timer0.h"
#include "Timer1.h"

char score[6] = {'S', 'c', 'o', 'r', 'e', ':'};

struct enemy{
	uint16_t X;
	uint16_t Y;
	const unsigned short *image;
	uint16_t hp;
	long dead;	// 1 means dead 0 means alive
};

typedef struct enemy enemy_t;
enemy_t Enemy;

struct player{
	uint16_t X;
	uint16_t Y;
	uint8_t lives;
	uint8_t dead;
	const unsigned short *image;
};

typedef struct player player_t;
player_t Player;

struct laser{
	uint16_t X;
	uint16_t Y;
	const unsigned short *image;
	uint8_t exist;
};

void Delay100ms(uint32_t count); // time delay in 0.1 seconds

void Delay100ms(uint32_t count){uint32_t volatile time;
  while(count>0){
    time = 727240;  // 0.1sec at 80 MHz
    while(time){
	  	time--;
    }
    count--;
  }
}

void movePlayerLeft(){
	Player.X -= 2;
}

void movePlayerRight(){
	Player.X += 2;
}

void noMove(){
	Player.X = Player.X;
}
void playerShoot(){
	
}
int count=0;
void enemyMove(){
//	if(getFlag()	==1){
		count++;
		if(Enemy.X < 125 && (count%10 == 0))
			Enemy.X += 1;
		
		else if(Enemy.X >= 124){
			Enemy.Y += 20;
			Enemy.X = 0;
		}
		
		else if(Enemy.Y > 140){
			Player.lives--;
			Enemy.Y = 20;
			
		}
//	}
}


uint16_t getPlayerX(){
	return Player.X;
}


void SpaceInvaders_Init(){
	ST7735_FillScreen(0x0000);
	Player.X = 55;
	Player.Y = 145;
	Enemy.X = 55;
	Enemy.Y = 20;
	Player.image = PlayerShip0;
	Enemy.image = SmallEnemy30pointA;
	Enemy.hp = 100;
	Player.lives = 3;
	Player.dead = 0;
	Enemy.dead = 0;
	ST7735_DrawBitmap(Enemy.X, Enemy.Y, Enemy.image, 16, 10);
	ST7735_DrawBitmap(Player.X, Player.Y, Player.image, 18, 8);
	ST7735_SetCursor(12, 15);
	ST7735_OutString(score);
//	Timer1_Init(setFlag, 80000000/2); //
}

void DrawScreen(){
	ST7735_DrawBitmap(Enemy.X, Enemy.Y, Enemy.image, 16, 10);
	ST7735_DrawBitmap(Player.X, Player.Y, Player.image, 18, 8);
	ST7735_FillRect(0,150,30,10,0x0000);
}
