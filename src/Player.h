#include <Arduino.h>

class Player
{

private:
  unsigned short id = 0;
  unsigned short ballsDetected = 0;
  unsigned long score = 0;

public:
  Player(unsigned short id);
  void setId(unsigned short id);
  unsigned short getId();
  void addDetectedBall();
  short detectedBalls();
  void increaseScore(unsigned short points);
  unsigned long getScore();
};