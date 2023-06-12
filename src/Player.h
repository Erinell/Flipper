#include <Arduino.h>

#ifndef PLAYER_H
#define PLAYER_H

class Player
{

private:
  unsigned short id = 0; // index
  uint8_t ballsDetected = 0; // balle(s) jouée(s)
  unsigned long score = 0; // le score
  bool endGame = false; // partie terminée

public:
  // @param id index du joueur
  Player(uint8_t id);
  Player();

  uint8_t getId();
  void addDetectedBall();
  uint8_t detectedBalls();
  void increaseScore(int points);
  unsigned long getScore();
  String getScoreString();
  void setEndGame(bool endGame);
  bool isOut();
};

#endif