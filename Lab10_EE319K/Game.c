//game stuff!
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Sound.h"
#include "ADC.h"

struct enemy{
	unsigned long enemyX;
	unsigned long enemyY;
	const unsigned short *image;
	long life;	// 0 means dead 1 means alive
};

typedef struct enemy enemy_t;
enemy_t Enemy[5];

struct player{
	uint16_t playerX;
	uint16_t playerY;
	uint8_t lives;
	uint8_t dead;
	const unsigned short *image;
};

typedef struct player player_t;
player_t Player;

struct laser{
	uint16_t laserX;
	uint16_t laserY;
	const unsigned short *image;
	uint8_t exist;
};

void movePlayerLeft(){
	Player.playerX -= 2;
}

void movePlayerRight(){
	Player.playerX += 2;
}

void playerShoot(){
	
}
