
#include <Arduboy2.h>

Arduboy2 arduboy;

int gameState;
int lapsedTime;
int enemiesNum;
int nextEnemyStarts;
int score;

int playerPosX;
int playerPosY;
int playerSizeX;
int playerSizeY;
int playerLives;

int iEnemy;
int enemyPosX[8];
int enemyPosY[8];
int enemyIncX[8];
int enemyIncY[8];
int enemySizeX[8];
int enemySizeY[8];

const unsigned char playerMask[] PROGMEM = {
  0x7c, 0x6e, 0xdb, 0x9f, 0x9f, 0xdb, 0x6e, 0x7c, 
  };

const unsigned char enemy1Mask[] PROGMEM = {
  0x14, 0x52, 0x98, 0x27, 0xe4, 0x19, 0x4a, 0x28,
  };

const unsigned char enemy2Mask[] PROGMEM = {
  0xc1, 0x25, 0x5a, 0x24, 0x24, 0x5a, 0xa4, 0x83, 
  };

const unsigned char livesMask[] PROGMEM = {
  0x0e, 0x1b, 0x31, 0x7a, 0x3f, 0x1f, 0x0e, 0x00, 
  };

const unsigned char pointsMask[] PROGMEM = {
  0x3f, 0x09, 0x09, 0x06, 0x00, 0x1f, 0x24, 0x00, 0x24, 0x2a, 0x2a, 0x10,
  };

void setup() {

  gameState = 0;
  lapsedTime = 0;
  enemiesNum = 1;  
  nextEnemyStarts = 480;
  score = 0;
  
  playerPosX = 60; // ( hScreen - hPlayer ) / 2
  playerPosY = 28;
  playerSizeX = 8;
  playerSizeY = 8;
  playerLives = 4;
  
  enemyPosX[0] = 17;
  enemyPosY[0] = 1;
  enemyIncX[0] = 1;
  enemyIncY[0] = 1;
  enemySizeX[0] = 8;
  enemySizeY[0] = 8;
  
  enemyPosX[1] = 103;
  enemyPosY[1] = 1;
  enemyIncX[1] = -1;
  enemyIncY[1] = 1;
  enemySizeX[1] = 8;
  enemySizeY[1] = 8;

  enemyPosX[2] = 17;
  enemyPosY[2] = 55;
  enemyIncX[2] = 1;
  enemyIncY[2] = -1;
  enemySizeX[2] = 8;
  enemySizeY[2] = 8;
  
  enemyPosX[3] = 103;
  enemyPosY[3] = 55;
  enemyIncX[3] = -1;
  enemyIncY[3] = -1;
  enemySizeX[3] = 8;
  enemySizeY[3] = 8;

  arduboy.begin();
  arduboy.setFrameRate(60);
  }

void playBeep(int valFrequency) {
  //tone(PIN_SPEAKER_1, valFrequency, 20);
  }

void loop() {

  if (!(arduboy.nextFrame())) return;

  lapsedTime++;
  if ((lapsedTime%(60/enemiesNum))==0) score++;
  
  if (lapsedTime==nextEnemyStarts) {
    enemiesNum++;
    if (enemiesNum<4) nextEnemyStarts = lapsedTime + nextEnemyStarts + (nextEnemyStarts/2);
    tone(PIN_SPEAKER_1, 550, 150);
    }

  if (arduboy.pressed(UP_BUTTON) && playerPosY>1) playerPosY--;
  if (arduboy.pressed(DOWN_BUTTON) && playerPosY<55) playerPosY++;
  if (arduboy.pressed(LEFT_BUTTON) && playerPosX>17) playerPosX--;
  if (arduboy.pressed(RIGHT_BUTTON) && playerPosX<103) playerPosX++;

  if ((lapsedTime%2)==0) {

    for (iEnemy=0;iEnemy<enemiesNum;iEnemy++) {

      enemyPosX[iEnemy] += enemyIncX[iEnemy];
      enemyPosY[iEnemy] += enemyIncY[iEnemy];

      if (enemyPosX[iEnemy]==17) {
        enemyIncX[iEnemy] = 1;
        playBeep(440);
        }
      
      if (enemyPosX[iEnemy]==103) {
        enemyIncX[iEnemy] = -1;
        playBeep(440);
        }

      if (enemyPosY[iEnemy]==1) {
        enemyIncY[iEnemy] = 1;
        playBeep(440);
        }
      
      if (enemyPosY[iEnemy]==55) {
        enemyIncY[iEnemy] = -1;
        playBeep(440);
        }
      }
    }

  // --- Collision

  for (iEnemy=0;iEnemy<enemiesNum;iEnemy++) {

    if ((playerPosX<(enemyPosX[iEnemy]+enemySizeX[iEnemy]))&&((playerPosX+playerSizeX)>enemyPosX[iEnemy])&&(playerPosY<(enemyPosY[iEnemy]+enemySizeY[iEnemy]))&&((playerPosY+playerSizeY)>enemyPosY[iEnemy])) {
      //tone(PIN_SPEAKER_1, 550, 150);
      if (playerLives>0) playerLives--;
      }
    }

  arduboy.clear();
  arduboy.drawRect(16, 0, 96, 64, WHITE);
  
  arduboy.drawRect(playerPosX, playerPosY, playerSizeX, playerSizeY, WHITE); //arduboy.drawBitmap(playerPosX, playerPosY, playerMask, 8, 8, WHITE);

  for (iEnemy=0;iEnemy<enemiesNum;iEnemy++) {
    arduboy.fillRect(enemyPosX[iEnemy], enemyPosY[iEnemy], enemySizeX[iEnemy], enemySizeY[iEnemy], WHITE); //arduboy.drawBitmap(enemy1PosX, enemy1PosY, enemy1Mask, 8, 8, WHITE);  
    }
  
  if (playerLives>3) arduboy.drawBitmap(4, 12, livesMask, 8, 8, WHITE);
  if (playerLives>2) arduboy.drawBitmap(4, 23, livesMask, 8, 8, WHITE);
  if (playerLives>1) arduboy.drawBitmap(4, 34, livesMask, 8, 8, WHITE);
  if (playerLives>0) arduboy.drawBitmap(4, 45, livesMask, 8, 8, WHITE);
  
  arduboy.drawRect(0,0,15,10,WHITE);
  arduboy.drawRect(0,54,15,10,WHITE);
  arduboy.drawRect(113,0,15,10,WHITE);
  arduboy.drawRect(113,54,15,10,WHITE);
  arduboy.drawBitmap(115, 12, pointsMask, 12, 8, WHITE);
  arduboy.setCursor(118,21);
  arduboy.print(score/1000);
  arduboy.setCursor(118,29);
  arduboy.print((score/100)%10);
  arduboy.setCursor(118,37);
  arduboy.print((score/10)%10);
  arduboy.setCursor(118,45);
  arduboy.print(score%10);
  
  arduboy.display();
  }
