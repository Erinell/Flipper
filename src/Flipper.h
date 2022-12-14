#include <Player.h>

class Flipper
{
private:
  // config
  uint8_t maxPlayers;
  uint8_t maxTry;
  uint32_t startDelay;

  uint8_t currentMaxPlayers = 0;
  uint8_t playerTurn = 0;
  int8_t winnerId = -1;

  uint32_t timer = 0;
  bool maxPlayersUpdated;
  bool scoreUpdated;
  bool ballDetected;
  uint8_t playersOut;

  Player players[5] = {
    Player(0),
    Player(1),
    Player(2),
    Player(3),
    Player(4),
  };

public:
  Flipper(uint8_t maxPlayers, uint8_t maxTry, uint32_t startDelay);

  void init();
  bool canStart();

  void updatePlayer();
  void updateScore();

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
  void ejection();
};