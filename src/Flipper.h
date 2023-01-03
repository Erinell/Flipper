#include <Player.h>

class Flipper
{
private:
  // config
  unsigned short maxPlayers;
  unsigned short maxTry;
  unsigned short startDelay;

  unsigned short currentMaxPlayers = 0;
  unsigned short playerTurn = 0;
  int8_t winnerId = -1;

  long timer = 0;
  bool maxPlayersUpdated;
  bool scoreUpdated;
  bool ballDetected;
  Player players[5] = {
    Player(0),
    Player(1),
    Player(2),
    Player(3),
    Player(4),
  };

public:
  /*
   * @param maxPlayers Nombre de joueurs dans la partie
   * @param maxTry Nombre de balle par joueur
   * @param startDelay délai de démarrage de la partie
   */
  Flipper(unsigned short maxPlayers, unsigned short maxTry, unsigned short startDelay);

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
  unsigned short getMaxPlayer();
  short getTimer();
  void resetBonus();
  void setPlayerOut(uint8_t i);
  void updateWinnerId();
  int8_t getWinnerId();
  void ejection();
};