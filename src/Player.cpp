#include "Player.h"
#include <Arduino.h>
Player::Player()
{
}

Player::Player(uint8_t id)
{
  this->id = id;
}

uint8_t Player::getId()
{
  return this->id;
}

void Player::addDetectedBall()
{
  this->ballsDetected++;
}

uint8_t Player::detectedBalls()
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
 char score[9];
 sprintf(score, "%09lu", this->score);
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

