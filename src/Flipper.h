#include "Player.h"
#include "Pins.h"
#include "macro.h"
#include "Sanity.h"

class Flipper
{
private:
  uint8_t maxPlayers;
  uint8_t maxTry;
  uint32_t startDelay;

  uint8_t points[COUNT(_points_pin)] = SCORE;
  uint16_t points_value[COUNT(_points_value)] = SCORE_VALUE;

  uint8_t bonus_pin[COUNT(_bonus_pin)] = BONUS;
  uint16_t bonus_value[COUNT(_bonus_value)] = BONUS_VALUE;
  uint8_t leds_bonus[COUNT(_bonus_led)] = LEDS_BONUS;

  uint8_t solenoids_pin[COUNT(_solenoids_pin)] = SOLENOIDS;
  uint8_t trigger_solenoid_pin[COUNT(_trigger_solenoids_pin)] = TRIGGER_SOLENOID;

  uint8_t currentMaxPlayers = 0;
  uint8_t playerTurn = 0;
  int8_t winnerId = -1;

  uint32_t timer = 0;
  bool maxPlayersUpdated;
  bool scoreTriggered;
  bool scoreUpdated;
  bool ballDetected;
  uint8_t playersOut;

  Player players[MAX_PLAYERS];

public:
  Flipper(uint8_t maxPlayers, uint8_t maxTry, uint32_t startDelay);

  void init();
  bool canStart();

  void updatePlayer();
  bool updateScore();

  bool isBallDetected();
  bool isTilted();
  bool startPressed();
  Player currentPlayer();
  Player getPlayer(uint8_t i);
  Player* getPlayers();
  void nextPlayer();
  short getMaxTry();
  uint8_t getMaxPlayer();
  long getTimer();
  void resetBonus();
  uint8_t getPlayersOut();
  void updateWinnerId();
  int8_t getWinnerId();
  void ejectBall();
  void resetTargets();
  void EnableBatteurs(bool enable);
  void triggerSolenoids();
};