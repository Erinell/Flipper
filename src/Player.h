#include <Arduino.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{

private:
  unsigned short id = 0; // index
  unsigned short ballsDetected = 0; // balle(s) jouée(s)
  unsigned long score = 0; // le score
  bool endGame = false; // partie terminée

public:
  // @param id index du joueur
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