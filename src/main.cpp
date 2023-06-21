#include <Arduino.h>
#include <SPI.h>
#include "Colors.h"
#include <RGBmatrixPanel.h>
#include <Fonts/FreeSans9pt7b.h>
#include "Flipper.h"
#include "Player.h"

RGBmatrixPanel display(A, B, C, D, CLK, LAT, OE, false, 64);

Flipper flipper(MAX_PLAYERS, MAX_TRY, START_DELAY);

void (*resetFunc)(void) = 0; // reset soft

const unsigned char tete[] PROGMEM = {
    // 'tete, 8x10px
    0x3c, 0x42, 0x81, 0xa5, 0x81, 0x81, 0xa5, 0x99, 0x42, 0x3c};

const unsigned char teteSoso[] PROGMEM = {
    // 'tete_soso, 8x10px
    0x3c, 0x42, 0x81, 0xa5, 0x81, 0x81, 0xbd, 0x81, 0x42, 0x3c};

const unsigned char teteSad[] PROGMEM = {
    // 'tete_sad, 8x10px
    0x3c, 0x42, 0x81, 0xa5, 0x81, 0x99, 0xa5, 0x81, 0x42, 0x3c};

const unsigned char selector[] PROGMEM = {
    // 'selector', 6x4px
    0x84, 0xcc, 0x78, 0x30};

void scrollString(String str)
{

  display.fillScreen(BLACK);
  display.setTextWrap(false);
  display.setTextSize(2);
  int charWidth = 12;
  int pxwidth = (str.length() * charWidth) + 32;
  display.setFont();
  display.setTextColor(BLUE, BLACK);
  for (int32_t x = charWidth; x >= -pxwidth; x--)
  {
    display.setCursor(x * 2, 8);
    display.print(str);
  }
}

void initGame()
{
  flipper.init();

  display.setTextColor(RED, BLACK);
  display.setFont();
  display.setTextSize(2);
  // scrollString("Aucune balle");
  String txt = "Aucune balle";
  int x = 0;
  int pxwidth = (txt.length() * 12);
  while (!flipper.isBallDetected())
  {
    display.setCursor(x * 2, 6);
    display.print(txt);

    x--;
    if (x < -pxwidth)
    {
      x = 0;
    }
    // display.setCursor(2, 13);
    // display.print("Aucune");
    // display.setCursor(12, 29);
    // display.print("Balle");
  }
  display.fillScreen(BLACK);
  display.setFont();
  display.setTextColor(GREEN, BLACK);

  while (!flipper.canStart())
  {
    display.setTextSize(2);
    display.setCursor(27, 1);
    display.print(String(round(flipper.getTimer() / 900)));
    display.setTextSize(1);
    display.setCursor(5, 20);
    display.print("Joueurs:");
    display.print(String(flipper.getMaxPlayer()));
  }

  flipper.updatePlayer();
  flipper.EnableBatteurs(true);

  display.fillScreen(BLACK);
  display.drawRect(0, 0, 64, 32, BLUE);
}

void setup()
{
  digitalWrite(reset, HIGH);

  Serial.begin(9600);
  display.begin();
  display.fillScreen(BLACK);
  display.setTextWrap(false);
  display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);

  initGame();
}

void showScore(int x, int y, unsigned long score, uint16_t color)
{
  char _score[9];
  // sprintf(score, "%09lu", this->score);
  sprintf(_score, "%9lu", score);
  String str_score = _score;
  display.setTextColor(color, BLACK);
  display.setCursor(x, y);
  display.print(str_score.substring(0, 3));
  if (score > 999999)
    display.drawPixel(x + 18, y + 6, color);
  display.setCursor(x + 20, y);
  display.print(str_score.substring(3, 6));
  if (score > 999)
    display.drawPixel(x + 38, y + 6, color);
  display.setCursor(x + 40, y);
  display.print(str_score.substring(6, 9));
}

void showPlayers(int x, int y, bool end = false)
{
  if (!end)
  {
    for (size_t i = 0; i < flipper.getMaxPlayer(); i++)
    {
      display.setTextColor(CYAN, BLACK);
      display.setCursor(x * i + 11, y + 2);
      display.print(flipper.getMaxTry() - flipper.getPlayer(i).detectedBalls());

      if (flipper.getPlayer(i).isOut() && flipper.getMaxPlayer() > 1)
      {
        display.drawBitmap(x * i + 2, y, teteSoso, 8, 10, ORANGE, BLACK);
      }

      if (!flipper.getPlayer(i).isOut())
      {
        display.drawBitmap(x * i + 2, y, tete, 8, 10, GREEN, BLACK);
      }

      display.fillRect(x * i + 3, y - 5, 6, 4, BLACK);
      if (flipper.currentPlayer().getId() != i)
        continue;

      display.drawBitmap(x * i + 3, y - 5, selector, 6, 4, BLUE);
    }
    return;
  }

  display.fillRect(x * 0 + 3, y - 5, 51, 4, BLACK);

  for (uint8_t i = 0; i < flipper.getMaxPlayer(); i++)
  {
    if (flipper.getWinnerId() == i)
    {
      display.drawBitmap(x * flipper.getWinnerId() + 2, y, tete, 8, 10, GREEN, BLACK);
      continue;
    }
    display.drawBitmap(x * i + 2, y, teteSad, 8, 10, RED, BLACK);
  }
}

void tilted()
{
  display.fillRect(1, 1, 62, 30, BLACK);
  display.setTextColor(RED, BLACK);
  display.setTextSize(1);
  display.setCursor(12, 2);
  display.print("Flipper");
  display.setCursor(12, 13);
  display.print("Bascul");
  display.drawChar(48, 13, 0x82, RED, BLACK, 1);

  delay(3000); // blocage batteurs, temps pour simuler la chute de la bille

  flipper.resetBonus();
  flipper.nextPlayer();
  display.fillRect(1, 1, 62, 30, BLACK);
}

void endgame()
{
  flipper.updateWinnerId();
  flipper.nextPlayer();

  showPlayers(15, 20, true);
  showScore(4, 2, flipper.getPlayer(flipper.getWinnerId()).getScore(), YELLOW);

  display.setTextColor(BLUE, BLACK);
  display.setCursor(22, 11);
  display.print("FIN!");

  flipper.EnableBatteurs(false);

  delay(END_DELAY); // un certains temps avant reset
  SOFT_RESET ? resetFunc() : digitalWrite(reset, LOW);

  while (true) // boucle (temporaire) anti retour
  {
  }
}

void loop()
{
  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore();
  flipper.triggerSolenoids();

  if (flipper.isTilted())
  {
    tilted();
  }

  showScore(4, 2, currentPlayer.getScore(), YELLOW);
  showPlayers(15, 20);

  // bille perdue
  if (currentPlayer.detectedBalls() < flipper.getMaxTry())
  {
    if (!flipper.isBallDetected())
    {
      return;
    }
    flipper.resetBonus();
    flipper.nextPlayer();
    flipper.ejectBall();

    flipper.resetTargets();
    return;
  }

  if (flipper.getPlayersOut() >= flipper.getMaxPlayer())
  {
    endgame();
  }
}
