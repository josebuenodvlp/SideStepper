
#include <Arduboy2.h>

Arduboy2 arduboy;

int enemiesNum;
int lapsedTime;
int playerPosX;
int playerPosY;
int playerLives;
int enemy1PosX;
int enemy1PosY;
int enemy1IncX;
int enemy1IncY;
int enemy2PosX;
int enemy2PosY;
int enemy2IncX;
int enemy2IncY;

const unsigned char playerMask[] PROGMEM = {
  0x7c, 0x6e, 0xdb, 0x9f, 0x9f, 0xdb, 0x6e, 0x7c, 
  };

const unsigned char livesMask[] PROGMEM = {
  0x0e, 0x1b, 0x31, 0x7a, 0x3f, 0x1f, 0x0e, 0x00, 
  };

const unsigned char enemy1Mask[] PROGMEM = {
  0x14, 0x52, 0x98, 0x27, 0xe4, 0x19, 0x4a, 0x28,
  };

const unsigned char enemy2Mask[] PROGMEM = {
  0xc1, 0x25, 0x5a, 0x24, 0x24, 0x5a, 0xa4, 0x83, 
  };

const unsigned char pointsMask[] PROGMEM = {
  0x3f, 0x09, 0x09, 0x06, 0x00, 0x1f, 0x24, 0x00, 0x24, 0x2a, 0x2a, 0x10,
  };
  
void setup() {
  
  arduboy.begin();
  enemiesNum = 1;  
  lapsedTime = 0;
  playerPosX = 60; // ( hScreen - hPlayer ) / 2
  playerPosY = 28;
  playerLives = 4;
  enemy1PosX = 17;
  enemy1PosY = 1;
  enemy1IncX = 1;
  enemy1IncY = 1;
  enemy2PosX = 103;
  enemy2PosY = 1;
  enemy2IncX = -1;
  enemy2IncY = 1;
}

void playBeep1() {
  tone(PIN_SPEAKER_1, 440, 20);
  }

void playBeep2() {
  tone(PIN_SPEAKER_1, 330, 20);
  }
void loop() {

  if (!(arduboy.nextFrame())) return;

  lapsedTime++;
  if (lapsedTime==240) {
    enemiesNum++;
          tone(PIN_SPEAKER_1, 550, 150);

  }

  if (arduboy.pressed(UP_BUTTON) && playerPosY>1) playerPosY--;
  if (arduboy.pressed(DOWN_BUTTON) && playerPosY<55) playerPosY++;
  if (arduboy.pressed(LEFT_BUTTON) && playerPosX>17) playerPosX--;
  if (arduboy.pressed(RIGHT_BUTTON) && playerPosX<103) playerPosX++;

  enemy1PosX += enemy1IncX;
  enemy1PosY += enemy1IncY;
  
  if (enemy1PosX==17) {
    enemy1IncX=1;
    playBeep1();
  }
  if (enemy1PosX==103) {
    enemy1IncX=-1;
    playBeep1();
  }
  if (enemy1PosY==1) {
    enemy1IncY=1;
    playBeep1();
  }
  if (enemy1PosY==55) {
    enemy1IncY=-1;
    playBeep1();
  }

  if (enemiesNum>1) {
    enemy2PosX += enemy2IncX;
    enemy2PosY += enemy2IncY;
    
    if (enemy2PosX==17) {
      enemy2IncX=1;
      playBeep2();
    }
    if (enemy2PosX==103) {
      enemy2IncX=-1;
      playBeep2();
    }
    if (enemy2PosY==1) {
      enemy2IncY=1;
      playBeep2();
    }
    if (enemy2PosY==55) {
      enemy2IncY=-1;
      playBeep2();
    }
  }
  
  arduboy.clear();
  arduboy.drawRect(16, 0, 96, 64, WHITE);
  arduboy.drawBitmap(playerPosX, playerPosY, playerMask, 8, 8, WHITE);
  arduboy.drawBitmap(enemy1PosX, enemy1PosY, enemy1Mask, 8, 8, WHITE);
  if (enemiesNum>1) arduboy.drawBitmap(enemy2PosX, enemy2PosY, enemy2Mask, 8, 8, WHITE);
  if (playerLives>3) arduboy.drawBitmap(4, 12, livesMask, 8, 8, WHITE);
  if (playerLives>2) arduboy.drawBitmap(4, 23, livesMask, 8, 8, WHITE);
  if (playerLives>1) arduboy.drawBitmap(4, 34, livesMask, 8, 8, WHITE);
  if (playerLives>0) arduboy.drawBitmap(4, 45, livesMask, 8, 8, WHITE);
  arduboy.drawRect(0,0,15,10,WHITE);
  arduboy.drawRect(0,54,15,10,WHITE);
  arduboy.drawRect(113,0,15,10,WHITE);
  arduboy.drawRect(113,54,15,10,WHITE);
  arduboy.drawBitmap(115, 12, pointsMask, 12, 8, WHITE);
  arduboy.display();
}
