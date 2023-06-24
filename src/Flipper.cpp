#include "Flipper.h"
#include <Arduino.h>
#include "Pins.h"

Flipper::Flipper(uint8_t maxPlayers, uint8_t maxTry, uint32_t startDelay)
{
  this->maxPlayers = maxPlayers;
  this->maxTry = maxTry;
  this->startDelay = startDelay;
}

void Flipper::init()
{
  for (uint8_t i = 0; i < sizeof(this->points); i++)
  {
    pinMode(this->points[i], INPUT);
  }
  for (uint8_t i = 0; i < sizeof(this->bonus_pin); i++)
  {
    pinMode(this->bonus_pin[i], INPUT);
  }
  for (uint8_t i = 0; i < sizeof(this->leds_bonus); i++)
  {
    pinMode(this->leds_bonus[i], OUTPUT);
  }

  for (uint8_t i = 0; i < sizeof(this->solenoids_pin); i++)
  {
    pinMode(this->solenoids_pin[i], OUTPUT);
  }

  for (uint8_t i = 0; i < sizeof(this->trigger_solenoid_pin); i++)
  {
    pinMode(this->trigger_solenoid_pin[i], INPUT);
  }

  pinMode(credits, INPUT);
  pinMode(start, INPUT);
  pinMode(ballDetection, INPUT);
  pinMode(tilt, INPUT);
  pinMode(ballEjection, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(batteurs, OUTPUT);
  pinMode(liftTargets, OUTPUT);
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
  }

  if (this->maxPlayersUpdated)
  {
    if (this->startPressed() && this->timer <= 0)
    {
      return true;
    }
    if (!this->startPressed())
    {
      this->maxPlayersUpdated = false;
    }
  }
  if (millis() - this->timer >= this->startDelay)
  {
    this->timer = 0;
    return true;
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

  return digitalRead(ballDetection);
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
  this->scoreUpdated = false;
  this->players[this->playerTurn].addDetectedBall();
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

uint8_t Flipper::getMaxPlayer()
{
  return this->currentMaxPlayers;
}

long Flipper::getTimer()
{
  return this->startDelay - (millis() - this->timer);
}

bool Flipper::updateScore()
{
  if (!this->scoreTriggered)
  {
    for (uint8_t i = 0; i < sizeof(this->points); i++)
    {
      if (digitalRead(this->points[i]) == LOW)
        continue;
      this->players[this->playerTurn].increaseScore(this->points_value[i]);
      this->scoreTriggered = true;
    }

    for (uint8_t i = 0; i < sizeof(this->bonus_pin); i++)
    {
      if (digitalRead(this->bonus_pin[i]) == LOW)
        continue;
      if (digitalRead(this->leds_bonus[i]) == HIGH)
      {
        this->players[this->playerTurn].increaseScore(this->bonus_value[i] * 2);
        this->scoreTriggered = true;
      }
      if (digitalRead(this->leds_bonus[i]) == LOW)
      {
        this->players[this->playerTurn].increaseScore(this->bonus_value[i]);
        this->scoreTriggered = true;
        digitalWrite(this->leds_bonus[i], HIGH);
      }
    }
  }

  if (this->scoreTriggered)
  {
    this->scoreUpdated = true;
    bool allLow = true;
    for (uint8_t i = 0; i < sizeof(this->points); i++)
    {
      if (digitalRead(this->points[i]) == LOW)
        continue;
      allLow = false;
      break;
    }

    for (uint8_t i = 0; i < sizeof(this->bonus_pin); i++)
    {
      if (digitalRead(this->bonus_pin[i]) == LOW)
        continue;
      allLow = false;
      break;
    }

    if (allLow)
    {
      this->scoreTriggered = false;
    }
  }
  delay(5);
  return this->scoreUpdated;
}

void Flipper::resetBonus()
{
  for (uint8_t i = 0; i < sizeof(this->leds_bonus); i++)
  {
    digitalWrite(leds_bonus[i], LOW);
  }
}

uint8_t Flipper::getPlayersOut()
{
  this->playersOut = 0;
  for (size_t i = 0; i < this->currentMaxPlayers; i++)
  {
    if (this->players[i].detectedBalls() >= this->maxTry)
    {
      this->players[i].setEndGame(true);

      this->playersOut++;
    }
  }
  // if (this->playersOut > this->currentMaxPlayers)
  // {
  //   this->playersOut = 0;
  // }

  return this->playersOut;
}

void Flipper::updateWinnerId()
{
  for (uint8_t i = 0; i < this->currentMaxPlayers; i++)
  {
    bool isSolo = (this->currentMaxPlayers == 1 && this->players[this->playerTurn].getScore() > 0);
    if (this->players[i].getScore() > this->players[this->winnerId < 0 ? 0 : this->winnerId].getScore() || isSolo)
    {
      this->winnerId = i;
    }
  }
}

int8_t Flipper::getWinnerId()
{
  return this->winnerId > -1 ? this->winnerId : 0;
}

void Flipper::ejectBall()
{
  delay(1000);
  digitalWrite(ballEjection, HIGH);
  delay(TIMER_SOLENOIDS);
  digitalWrite(ballEjection, LOW);
  delay(1000); // eviter spam (a changer)
}

void Flipper::resetTargets()
{
  digitalWrite(liftTargets, HIGH);
  delay(TIMER_SOLENOIDS);
  digitalWrite(liftTargets, LOW);
}

void Flipper::EnableBatteurs(bool enable)
{
  digitalWrite(batteurs, enable ? HIGH : LOW);
}

// bool triggered = false;
void Flipper::triggerSolenoids()
{
  for (uint8_t i = 0; i < sizeof(this->trigger_solenoid_pin); i++)
  {
    if (digitalRead(this->trigger_solenoid_pin[i]) == LOW)
      continue;
    digitalWrite(this->solenoids_pin[i], HIGH);
    delay(TIMER_SOLENOIDS);
    digitalWrite(this->solenoids_pin[i], LOW);
  }
  // if (!triggered)
  // {
  //   for (uint8_t i = 0; i < sizeof(this->trigger_solenoid_pin); i++)
  //   {
  //     if (digitalRead(this->trigger_solenoid_pin[i]) == LOW)
  //       continue;
  //     digitalWrite(this->solenoids_pin[i], HIGH);
  //     delay(TIMER_SOLENOIDS);
  //     digitalWrite(this->solenoids_pin[i], LOW);
  //     triggered = true;
  //   }
  // }

  // if (triggered)
  // {
  //   bool allLow = true;
  //   for (uint8_t i = 0; i < sizeof(this->trigger_solenoid_pin); i++)
  //   {
  //     if (digitalRead(this->trigger_solenoid_pin[i]) == LOW)
  //       continue;
  //     allLow = false;
  //     break;
  //   }

  //   if (allLow)
  //   {
  //     triggered = false;
  //   }
  // }
}