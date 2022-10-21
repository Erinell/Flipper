#include "Flipper.h"
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

/*
 * Gestion appui start pour augmenter le nombre de joueurs.
 * TODO: revenir à zero si joueur max > config.
 */
bool Flipper::canStart()
{
  if (this->maxPlayers >= this->currentMaxPlayers)
  {
    return true;
  }

  if (this->currentMaxPlayers < this->maxPlayers)
  {
    if (digitalRead(start) == HIGH)
    {
      this->currentMaxPlayers++;
      this->timer = millis();
    }
    else if (millis() - this->timer >= this->startDelay)
    {
      this->timer = 0;
      return true;
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
  if (digitalRead(ballDetection) == HIGH)
  {
    return true;
  }
  return false;
}

Player Flipper::currentPlayer()
{
  return this->players[this->playerTurn];
}

short Flipper::getMaxTry()
{
  return this->maxTry;
}

void Flipper::updateScore(Player currentPlayer)
{
  if (!this->scoreUpdated)
  {
    if (digitalRead(points10) == HIGH)
    {
      currentPlayer.increaseScore(10);
      this->scoreUpdated = true;
    }
    if (digitalRead(points100) == HIGH)
    {
      currentPlayer.increaseScore(100);
      this->scoreUpdated = true;
    }
    if (digitalRead(points1000) == HIGH)
    {
      currentPlayer.increaseScore(1000);
      this->scoreUpdated = true;
    }
    if (digitalRead(points10000) == HIGH)
    {
      currentPlayer.increaseScore(10000);
      this->scoreUpdated = true;
    }
  }

  if (this->scoreUpdated)
  {
    if (digitalRead(points10) == LOW ||
        digitalRead(points100) == LOW ||
        digitalRead(points1000) == LOW ||
        digitalRead(points10000) == LOW)
    {
      this->scoreUpdated = false;
    }
  }
}