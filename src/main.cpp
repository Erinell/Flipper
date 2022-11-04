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

  while (!flipper.isBallDetected())
  {
    Serial.println("Balle absente, impossible de démarrer.");
  }

  while (!flipper.canStart())
  {
    Serial.print("Démarrage dans : ");
    Serial.println(flipper.getTimer());
  }

  Serial.print("Démarrage de la partie avec ");
  Serial.print(flipper.getMaxPlayer());
  Serial.println(" joueur(s).");

  flipper.updatePlayer();

}

void loop()
{
  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore();

  Serial.print("Joueur ");
  Serial.print(currentPlayer.getId());
  Serial.print(" : ");
  Serial.print(currentPlayer.getScore());
  Serial.print(" points, ");
  Serial.print(currentPlayer.detectedBalls());
  Serial.println(" coups");

  if (!flipper.isBallDetected())
  {
    return;
  }

  if (currentPlayer.detectedBalls() < flipper.getMaxTry())
  {
    flipper.nextPlayer();
  }

  if (currentPlayer.detectedBalls() >= flipper.getMaxTry())
  {
    currentPlayer.setEndGame(true);
    while (currentPlayer.isOut())
    {
      flipper.nextPlayer();
    }
  }

  flipper.ejection();
}
