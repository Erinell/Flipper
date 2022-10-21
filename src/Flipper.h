#include <Player.h>

class Flipper
{
private:
  // config
  unsigned short maxPlayers;
  unsigned short maxTry;
  unsigned short startDelay;

  // state
  short currentMaxPlayers = 0;
  short playerTurn = 0;

  long timer = 0;
  bool scoreUpdated = false;
  Player players[];

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
  bool isBallDetected();
  Player currentPlayer();
  short getMaxTry();
  void updateScore(Player currentPlayer);
};