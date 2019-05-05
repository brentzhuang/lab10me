// Game.h
// Header for Game.c

#ifndef GAME_H // do not include more than once
#define GAME_H

/* RandomNumber
input: int
output: int
returns random integer from 0 to (number - 1)
*/
uint32_t RandomNumber(uint32_t number);

/* SpaceInvader_Init
input: none
output: none
Initializes space invader portion of game
*/
void SpaceInvader_Init(void);

/* GameOver
input: none
output: none
Implements game over state
*/
void GameOver(void);

/* Victory
input: none
output: none
Implements victory state
*/
void Victory(void);

/* UpdateScore
Updates score on screen.
*/
void UpdateScore(int score);

/* PlayerXMove
input: none
output: none
Moves player model on X-axis, if ADC surpasses left threshold, move left
if ADC surpasses right threshold, move right
*/
void PlayerXMove(void);

/* EnemyMoveRight
input: none
output: none
Moves enemy aliens right along X-axis
*/
void EnemyMoveRight(void);

/* EnemyMoveLeft
input: none
output: none
Moves enemy aliens left along X-axis
*/
void EnemyMoveLeft(void);

/* EnemyMoveDown
input: none
output: none
Moves enemy down along Y-axis
*/
void EnemyMoveDown(void);

/* EnemyMovement
input: none
output: none
Moves enemies using EnemyMoveLeft, EnemyMoveRight, EnemyMoveDown
*/
void EnemyMovement(void);

/* PlayerLaserMove
input: none
output: none
Moves player lasers up y-axis to enemies
*/
void PlayerLaserMove(void);

/* EnemyLaserMove
input: none
output: none
Moves enemy lasers down y-axis towards player
*/
void EnemyLaserMove(void);

/* Movement
input: none
output: none
Moves objects that have motion
*/
void Movement(void);

/* DrawPauseScreen
input: none
output: none
Draws a pause screen while the game is paused
*/
void DrawPauseScreen(void);

/* DrawGameOverScreen
input: none
output: none
Draws game over screen
*/
void DrawGameOverScreen(void);

/* DrawVictoryScreen
input: none
output: none
Draws victory screen
*/
void DrawVictoryScreen(void);

/* DrawPlayer
input: none
output: none
Draws player model on LCD if player is alive, draws explosion if player has recently died
*/
void DrawPlayer(void);

/* DrawEnemy
input: none
output: none
Draws enemies on LCD if enemy is alive, draws explosion if enemy has recently died
*/
void DrawEnemy(void);

/* DrawBunker
input: none
output: none
Draws bunkers on LCD if they are alive
*/
void DrawBunker(void);

/* DrawPlayerLaser
input: none
output: none
Draws Player lasers on LCD
*/
void DrawPlayerLaser(void);

/* DrawEnemyLaser
input: none
output: none
Draws Enemy lasers on LCD
*/
void DrawEnemyLaser(void);

/* Draw
input: none
output: none
Draws entire frame on LCD
*/
void Draw(void);

/* PlayerFire
input: none
output: none
Fires a laser from player model if player has not exceeded maximum lasers
*/
void PlayerFire(void);

/* EnemyFire
input: none
output: none
Cycles through a certain delay, then fires at random from a random
living enemy if maximum enemy lasers has not been surpassed.
*/
void EnemyFire(void);

/* PlayerHitReg
input: none
output: none
Check if player has been hit by laser
*/
void PlayerHitReg(void);

/* EnemyHitReg
input: none
output: none
Check if enemy has been hit by laser
*/
void EnemyHitReg(void);

/* BunkerEnemyHitReg
input: none
output: none
Check if bunker has been hit by enemy laser
*/
void BunkerEnemyHitReg(void);

/* BunkerPlayerHitReg
input: none
output: none
Check if bunker has been hit by player laser
*/
void BunkerPlayerHitReg(void);

/* HitReg
input: none
output: none
Checks hit registration.
*/
void HitReg(void);

/* Pause
input: none
output: none
Pauses the game.
*/
void Pause(void);

/* GameState
input: none
output: int
Checks if player has completed the game or died
*/
void SpaceInvader(void);

#endif
