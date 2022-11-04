#include <Arduino.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{

private:
  unsigned short id = 0;
  unsigned short ballsDetected = 0;
  unsigned long score = 0;
  bool endGame = false;

public:
  Player(unsigned short id);
  void setId(unsigned short id);
  unsigned short getId();
  void addDetectedBall();
  short detectedBalls();
  void increaseScore(int points);
  unsigned long getScore();
  void setEndGame(bool endGame);
  bool isOut();
};

#endif