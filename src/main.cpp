#include <Arduino.h>
#include <Flipper.h>
#include <Player.h>

const unsigned short maxPlayers = 4;
const unsigned short maxTry = 3;
const unsigned short startDelay = 5000;

Flipper flipper(maxPlayers, maxTry, startDelay);

void setup()
{
  flipper.init();

  Serial.begin(9600);

   while (!flipper.canStart())
  {
    Serial.print("temps restant : ");
     Serial.println(flipper.getTimer());
    // Serial.print(" | ");
    // Serial.println(flipper.getMaxPlayer());
  
     // en attente d'appui sur bouton start
     // incrémente nombre joueur
     // fin si délai > config (ici 5 sec) ou nombre joueur == joueur max config
     // on peux update l'afficheur ici pour le nombre de joueur en temps réel
   }

  // while (!flipper.isBallDetected())
  //{
  //   Serial.println("Balle absente, impossible de démarrer.");
  //   // tant que pas de bille,
  //   // on l'affiche et ça démarre pas.
  // }
  Serial.println("Démarrage de la partie...");

  flipper.updatePlayer();
}

void loop()
{

  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore();

  // flipper.nextPlayer();

  // if (flipper.isBallDetected() && currentPlayer.detectedBalls() >= flipper.getMaxTry())
  // {
  //   // partie fini pour ce joueur
  // }

  // if (flipper.isBallDetected() && currentPlayer.detectedBalls() < flipper.getMaxTry())
  // {
  //   // Passer au joueur suivant
  // }

  if (flipper.isBallDetected())
  {
    flipper.ejection();
  }


  // Serial.print(currentPlayer.getId());
  // Serial.print(" : ");
  // Serial.println(currentPlayer.getScore());
}