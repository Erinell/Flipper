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

  pinMode(bonus150, INPUT);
  pinMode(bonus250, INPUT);
  pinMode(bonus750, INPUT);
  pinMode(bonus1500, INPUT);

  pinMode(credits, INPUT);
  pinMode(start, INPUT);
  pinMode(ballDetection, INPUT);
  pinMode(tilt, INPUT);
  pinMode(ballEjection, OUTPUT);

  // debug LED
  pinMode(led150, OUTPUT);
  pinMode(led250, OUTPUT);
  pinMode(led750, OUTPUT);
  pinMode(led1500, OUTPUT);
}

bool Flipper::canStart()
{
  if (!this->maxPlayersUpdated)
  {

    if (this->startPressed())
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
    if (!this->startPressed())
    {
      this->maxPlayersUpdated = false;
    }
  }

  return false;
}

void Flipper::updatePlayer()
{
  for (uint16_t i = 0; i <= this->currentMaxPlayers; i++)
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
    // if (digitalRead(ballDetection) == HIGH)
    // {
    //   return true;
    // }
    if (digitalRead(ballDetection) == LOW)
    {
      this->ballDetected = false;
    }
  }

  return false;
}

bool Flipper::isTilted()
{
  if (digitalRead(tilt))
  {
    this->players[this->playerTurn].addDetectedBall();
    return true;
  }
  return false;
}

bool Flipper::startPressed()
{
  return digitalRead(start);
}

Player Flipper::getPlayer(uint8_t i)
{
  return this->players[i];
}

Player *Flipper::getPlayers()
{
  return this->players;
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

unsigned short Flipper::getMaxPlayer()
{
  return this->currentMaxPlayers;
}

short Flipper::getTimer()
{
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

    // Bonus
    if (digitalRead(bonus150) == HIGH)
    {
      if (digitalRead(led150) == HIGH)
      {
        this->players[this->playerTurn].increaseScore(300);
      }
      if (digitalRead(led150) == LOW)
      {
        this->players[this->playerTurn].increaseScore(150);
        digitalWrite(led150, HIGH);
      }
      this->scoreUpdated = true;
    }
    if (digitalRead(bonus250) == HIGH)
    {
      if (digitalRead(led250) == HIGH)
      {
        this->players[this->playerTurn].increaseScore(500);
      }
      if (digitalRead(led250) == LOW)
      {
        this->players[this->playerTurn].increaseScore(250);
        digitalWrite(led250, HIGH);
      }
      this->scoreUpdated = true;
    }
    if (digitalRead(bonus750) == HIGH)
    {
      if (digitalRead(led750) == HIGH)
      {
        this->players[this->playerTurn].increaseScore(1500);
      }
      if (digitalRead(led750) == LOW)
      {
        this->players[this->playerTurn].increaseScore(750);
        digitalWrite(led750, HIGH);
      }
      this->scoreUpdated = true;
    }
    if (digitalRead(bonus1500) == HIGH)
    {
      if (digitalRead(led1500) == HIGH)
      {
        this->players[this->playerTurn].increaseScore(3000);
      }
      if (digitalRead(led1500) == LOW)
      {
        this->players[this->playerTurn].increaseScore(1500);
        digitalWrite(led1500, HIGH);
      }
      this->scoreUpdated = true;
    }
  }

  if (this->scoreUpdated)
  {
    if (digitalRead(points10) == LOW &&
        digitalRead(points100) == LOW &&
        digitalRead(points1000) == LOW &&
        digitalRead(points10000) == LOW &&
        digitalRead(bonus150) == LOW &&
        digitalRead(bonus250) == LOW &&
        digitalRead(bonus750) == LOW &&
        digitalRead(bonus1500) == LOW)
    {
      this->scoreUpdated = false;
    }
  }
  delay(5);
}

void Flipper::resetBonus()
{
  digitalWrite(led150, LOW);
  digitalWrite(led250, LOW);
  digitalWrite(led750, LOW);
  digitalWrite(led1500, LOW);
}

void Flipper::setPlayerOut(uint8_t i)
{
  this->players[i].setEndGame(true);
}

void Flipper::updateWinnerId()
{
  for (uint8_t i = 0; i < this->currentMaxPlayers; i++)
  {
    uint8_t nextId = i + 1;
    if (nextId >= this->currentMaxPlayers - 1)
    {
      nextId = 0;
    }
    Serial.print(this->players[i].getScore());
    Serial.print(" ");
    Serial.println(this->players[nextId].getScore());

    bool isSolo = (this->currentMaxPlayers == 1 && this->players[this->playerTurn].getScore() > 0);
    if (this->players[i].getScore() > this->players[nextId].getScore() || isSolo)
    {
      this->winnerId = i;
      continue;
    }
  }
}

int8_t Flipper::getWinnerId()
{
  return this->winnerId;
}

void Flipper::ejection()
{
  digitalWrite(ballEjection, HIGH);
  delay(50);
  digitalWrite(ballEjection, LOW);
}
