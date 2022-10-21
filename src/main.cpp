#include <Arduino.h>
#include <Player.h>
#include <Flipper.h>

const unsigned short maxPlayers = 4;
const unsigned short maxTry = 3;
const unsigned short startDelay = 5000;


Flipper flipper(maxPlayers, maxTry, startDelay);

void setup()
{
  flipper.init();

  while (!flipper.canStart())
  {
    // en attente d'appui sur bouton start
    // incrémente nombre joueur
    // fin si délai > config (ici 5 sec) ou nombre joueur == joueur max config
    // on peux update l'afficheur ici pour le nombre de joueur en temps réel
  }

  flipper.updatePlayer();
}

void loop()
{
  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore(currentPlayer);

  if (flipper.isBallDetected() && currentPlayer.detectedBalls() >= flipper.getMaxTry())
  {
    // partie fini pour ce joueur
  }

  if (!flipper.isBallDetected())
  {
    // Afficher bille absente
  }
}
