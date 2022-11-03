#include "Flipper.h"
#include <Arduino.h>
#include <Pins.h>

Flipper::Flipper(unsigned short maxPlayers, unsigned short maxTry, unsigned short startDelay)
{
  this->maxPlayers = maxPlayers;
  this->maxTry = maxTry;
  this->startDelay = startDelay;
}

void Flipper::init()
{
  pinMode(points10, INPUT);
  pinMode(points100, INPUT);
  pinMode(points1000, INPUT);
  pinMode(points10000, INPUT);
  pinMode(credits, INPUT);
  pinMode(start, INPUT);
  pinMode(ballDetection, INPUT);
  pinMode(ballEjection, OUTPUT);
}

bool Flipper::canStart()
{
  if (!this->maxPlayersUpdated)
  {

    if (digitalRead(start) == HIGH)
    {
      if (this->currentMaxPlayers < this->maxPlayers)
      {
        this->currentMaxPlayers++;
      }
      else
      {
        this->currentMaxPlayers = 0;
      }
      this->maxPlayersUpdated = true;
      this->timer = millis();

      return false;
    }
    if (this->currentMaxPlayers <= 0)
    {
      this->timer = millis();
      return false;
    }

    if (millis() - this->timer >= this->startDelay)
    {
      this->timer = 0;
      return true;
    }
  }

  if (this->maxPlayersUpdated)
  {
    if (digitalRead(start) == LOW)
    {
      this->maxPlayersUpdated = false;
    }
  }

  return false;
}

void Flipper::updatePlayer()
{
  for (uint16_t i = 0; i < this->currentMaxPlayers; i++)
  {
    this->players[i] = Player(i);
  }
}

bool Flipper::isBallDetected()
{
  if (!this->ballDetected)
  {
    if (digitalRead(ballDetection) == HIGH)
    {
      this->ballDetected = true;
      this->players[this->playerTurn].addDetectedBall();
      return true;
    }
  }

  if (this->ballDetected)
  {
    if (digitalRead(ballDetection) == LOW)
    {
      this->ballDetected = false;
    }
  }

  return false;
}

Player Flipper::currentPlayer()
{
  return this->players[this->playerTurn];
}

void Flipper::nextPlayer()
{
  if (this->playerTurn < this->currentMaxPlayers - 1)
  {
    this->playerTurn++;
  }
  else
  {
    this->playerTurn = 0;
  }
}

short Flipper::getMaxTry()
{
  return this->maxTry;
}

short Flipper::getMaxPlayer()
{
  return this->currentMaxPlayers;
}

short Flipper::getTimer(){
  return this->startDelay - (millis() - this->timer);
}

void Flipper::updateScore()
{

  if (!this->scoreUpdated)
  {
    if (digitalRead(points10) == HIGH)
    {
      this->players[this->playerTurn].increaseScore(10);
      this->scoreUpdated = true;
    }
    if (digitalRead(points100) == HIGH)
    {
      this->players[this->playerTurn].increaseScore(100);
      this->scoreUpdated = true;
    }
    if (digitalRead(points1000) == HIGH)
    {
      this->players[this->playerTurn].increaseScore(1000);
      this->scoreUpdated = true;
    }
    if (digitalRead(points10000) == HIGH)
    {
      this->players[this->playerTurn].increaseScore(10000);
      this->scoreUpdated = true;
    }
  }

  if (this->scoreUpdated)
  {
    if (digitalRead(points10) == LOW &&
        digitalRead(points100) == LOW &&
        digitalRead(points1000) == LOW &&
        digitalRead(points10000) == LOW)
    {
      this->scoreUpdated = false;
    }
  }
  delay(50);
}

void Flipper::ejection()
{
  digitalWrite(ballEjection, HIGH);
  delay(50);
  digitalWrite(ballEjection, LOW);
}