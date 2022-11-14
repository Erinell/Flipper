#include "Player.h"
#include <Arduino.h>

Player::Player(unsigned short id)
{
  this->id = id;
}

unsigned short Player::getId()
{
  return this->id;
}

void Player::addDetectedBall()
{
  this->ballsDetected++;
}

short Player::detectedBalls()
{
  return this->ballsDetected;
}

void Player::increaseScore(int points)
{
  this->score += points;
}

unsigned long Player::getScore()
{
  return this->score;
}

String Player::getScoreString()
{
 char score[8];
 sprintf(score, "%07lu", this->score);
  return score;
}

void Player::setEndGame(bool endGame)
{
  this->endGame = endGame;
}

bool Player::isOut()
{
  return this->endGame;
}