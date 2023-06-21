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

void Player::setEndGame(bool endGame)
{
  this->endGame = endGame;
}

bool Player::isOut()
{
  return this->endGame;
}