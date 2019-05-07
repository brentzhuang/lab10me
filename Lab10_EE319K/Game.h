#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"


void SpaceInvaders_Init(void);
void movePlayerLeft(void);
void movePlayerRight(void);
void DrawScreen(void);
void noMove(void);
void enemyMove(void);
uint16_t getPlayerX(void);
void setFlag(void);
uint8_t getFlag(void);
void laserInit(void);
uint8_t getLaser(void);
void playerShoot(void);
void drawLaser(void);
uint16_t getLaserY(void);
void moveLaser(void);
uint16_t getLaserX(void);
uint16_t getEnemyX(void);
uint16_t getEnemyY(void);
void Hit(void);
void drawScore(void);
void hitDetect(uint16_t EnemyX, uint16_t EnemyY, uint8_t EnemyW, uint8_t EnemyH, uint16_t LaserX, uint16_t LaserY, uint8_t LaserW, uint8_t LaserH);
void checkEnd(void);
void Win(void);
void Lose(void);
