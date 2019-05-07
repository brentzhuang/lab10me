//game stuff!
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "ADC.h"
#include "ST7735.h"
#include "Images.h"
#include "Timer0.h"
#include "Timer1.h"

char score[8] = {'H', 'e', 'a', 'l', 't', 'h', ':', 0};
char win[9] = {'Y', 'o', 'u', ' ', 'w', 'i', 'n', '!', 0};
char lose[10] = {'Y', 'o', 'u', ' ', 'l', 'o', 's', 'e', '!', 0};
char hp[4] = {'H', 'p', ':', 0};

struct enemy{
	uint16_t X;
	uint16_t Y;
	const unsigned short *image;
	uint32_t hp;
	long dead;	// 1 means dead 0 means alive
};

typedef struct enemy enemy_t;
enemy_t Enemy;

struct player{
	uint16_t X;
	uint16_t Y;
	uint32_t lives;
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

typedef struct laser laser_t;
laser_t Laser;

void movePlayerLeft(){
	Player.X -= 2;
}

void movePlayerRight(){
	Player.X += 2;
}

void noMove(){
	Player.X = Player.X;
}

void laserInit(){
		Laser.X = Player.X +8;
		Laser.Y = Player.Y;
		Laser.image = PlayerLaser;
		Laser.exist = 1;
		Sound_Shoot();
}

uint8_t getLaser(){
	return Laser.exist;
}

uint16_t getLaserY(){
	return Laser.Y;
}

uint16_t getLaserX(){
	return Laser.X;
}

uint16_t getEnemyX(){
	return Enemy.X;
}

uint16_t getEnemyY(){
	return Enemy.Y;
}

void Hit(){
	Enemy.hp--;
	Laser.exist = 0;
	
}

void moveLaser(){
	Laser.Y--;
	if(Laser.Y == 2){
		Laser.exist = 0;
	}
}

void hitDetect(uint16_t EnemyX, uint16_t EnemyY, uint8_t EnemyW, uint8_t EnemyH, uint16_t LaserX, uint16_t LaserY, uint8_t LaserW, uint8_t LaserH){
	if(getLaser() == 1){
		for(uint8_t i = LaserX; i<=(LaserX+LaserW); i++){
			if((i>=EnemyX)&&(i<=(EnemyX+EnemyW))){
				for(uint8_t j = LaserY; j>=(LaserY-LaserH); j++){
					if((EnemyY>=j)&&((EnemyY-EnemyH))){
						while(Laser.exist == 1){
							Hit();
						}
					}
				}
			}
		}
	}
}

void drawLaser(){
	if(Laser.exist == 1){
		ST7735_DrawBitmap(Laser.X, Laser.Y, PlayerLaser, 2, 10);
	}
}

int count=0;
void enemyMove(){
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
}

void Win(){
	while(1){
	ST7735_FillScreen(0x0000);
	ST7735_SetCursor(0, 0);
	ST7735_OutString(win);
	}
}

void Lose(){
	ST7735_FillScreen(0x0000);
	ST7735_SetCursor(0, 0);
	ST7735_OutString(lose);
	while(1){
		
	}
}

void checkEnd(){
	if (Player.lives < 1){
		Lose();
	}
	if ((Enemy.hp <= 900) && (Enemy.hp > 100))
		Win();
}


void drawScore(){
	ST7735_SetCursor(17, 15);
	ST7735_OutUDec(Enemy.hp);
	ST7735_SetCursor(6, 15);
	ST7735_OutUDec(Player.lives);
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
	Laser.exist = 0;
	ST7735_DrawBitmap(Enemy.X, Enemy.Y, Enemy.image, 16, 10);
	ST7735_DrawBitmap(Player.X, Player.Y, Player.image, 18, 8);
	ST7735_SetCursor(9, 15);
	ST7735_OutString(score);
	ST7735_SetCursor(5, 15);
	ST7735_OutString(hp);
	
//	Timer1_Init(setFlag, 80000000/2); //
}

void DrawScreen(){
	ST7735_DrawBitmap(Enemy.X, Enemy.Y, Enemy.image, 16, 10);
	ST7735_DrawBitmap(Player.X, Player.Y, Player.image, 18, 8);
	ST7735_FillRect(0,150,30,10,0x0000);
}
