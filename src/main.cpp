#include <Arduino.h>
#include <SPI.h>
#include <DMD2.h>
#include <Font/SystemFont4x5.h>
#include <Font/SystemFont5x7.h>
// Flipper
#include <Flipper.h>
#include <Player.h>

SoftDMD display(1, 1);

const unsigned short maxPlayers = 4;
const unsigned short maxTry = 3;
const unsigned short startDelay = 5000;

Flipper flipper(maxPlayers, maxTry, startDelay);

void setup()
{
  flipper.init();

  Serial.begin(9600);
  display.setBrightness(20);
  display.begin();

  while (!flipper.isBallDetected())
  {
    display.selectFont(System4x5);
    display.drawString(4, 1, "PAS DE");
    display.drawString(6, 10, "BALLE");
  }

  display.clearScreen();

  while (!flipper.canStart())
  {
  //   Serial.print(flipper.getMaxPlayer());
  //   Serial.print(", ");
  //   Serial.println(round(flipper.getTimer() / 990));
    display.selectFont(System5x7);
    display.drawString(14, 1, String(round(flipper.getTimer() / 990)));
    display.selectFont(System4x5);
    display.drawString(1, 10, "J:");
    display.drawString(9, 10, String(flipper.getMaxPlayer()));
  }

  flipper.updatePlayer();

  display.clearScreen();
}

void loop()
{
  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore();

  display.drawString(1, 1, currentPlayer.getScoreString());
  display.drawString(1, 10, "J:");
  display.drawString(9, 10, String(currentPlayer.getId()));
  display.drawString(24, 10, "B2");

  //Serial.print("Joueur ");
  //Serial.print(currentPlayer.getId());
  //Serial.print(" : ");
  //Serial.print(currentPlayer.getScore());
  //Serial.print(" points, ");
  //Serial.print(currentPlayer.detectedBalls());
  //Serial.println(" coups");

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
      // TODO : fin de partie quand tout les joueurs ont fini.
    }
  }

  flipper.ejection();
}
