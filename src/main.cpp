#include <Arduino.h>
#include <SPI.h>
#include <Pins.h>
#include <Colors.h>
#include <RGBmatrixPanel.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Flipper.h>
#include <Player.h>

RGBmatrixPanel display(A, B, C, D, CLK, LAT, OE, false, 64);

const unsigned short maxPlayers = 4;
const unsigned short maxTry = 3;
const unsigned short startDelay = 5000;

Flipper flipper(maxPlayers, maxTry, startDelay);

// void (*resetFunc)(void) = 0; // fonction reset

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

void initGame()
{

  flipper.init();

  display.setTextColor(RED);
  while (!flipper.isBallDetected())
  {
    display.setCursor(2, 13);
    display.print("Aucune");
    display.setCursor(12, 29);
    display.print("Balle");
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

void showScore(int x, int y, String score, uint16_t color)
{
  display.setTextColor(color, BLACK);
  display.setCursor(x, y);
  display.print(score.substring(0, 3));
  display.drawPixel(x + 18, y + 6, color);
  display.setCursor(x + 20, y);
  display.print(score.substring(3, 6));
  display.drawPixel(x + 38, y + 6, color);
  display.setCursor(x + 40, y);
  display.print(score.substring(6, 9));
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

  display.fillRect(x * flipper.currentPlayer().getId() + 3, y - 5, 6, 4, BLACK);

  flipper.updateWinnerId();

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

void loop()
{
  Player currentPlayer = flipper.currentPlayer();

  flipper.updateScore();

  if (flipper.isTilted())
  {
    display.fillRect(1, 1, 62, 30, BLACK);
    display.setTextColor(RED, BLACK);
    display.setTextSize(1);
    display.setCursor(12, 2);
    display.print("Flipper");
    display.setCursor(12, 13);
    display.print("Bascul");
    display.drawChar(48, 13, 0x82, RED, BLACK, 1);
    delay(3000);
    // blocage batteur

    // if (flipper.getMaxPlayer() <= 1)
    // {
    //   resetFunc();
    // }

    flipper.nextPlayer();
    display.fillRect(1, 1, 62, 30, BLACK);
  }

  unsigned short playersOut = 0;
  for (size_t i = 0; i < flipper.getMaxPlayer(); i++)
  {
    if (flipper.getPlayer(i).detectedBalls() >= flipper.getMaxTry())
    {
      flipper.setPlayerOut(i);
      playersOut++;
    }
  }

  showScore(4, 2, currentPlayer.getScoreString(), YELLOW);
  showPlayers(15, 20);

  if (currentPlayer.detectedBalls() < flipper.getMaxTry())
  {
    if (!flipper.isBallDetected())
    {
      return;
    }
    flipper.resetBonus();
    flipper.nextPlayer();
  }

  while (playersOut >= flipper.getMaxPlayer())
  {
    display.setTextColor(BLUE, BLACK);
    display.setCursor(22, 11);
    display.print("FIN!");
    showPlayers(15, 20, true);
    showScore(4, 2, flipper.getPlayer(flipper.getWinnerId()).getScoreString(), YELLOW);
    
    delay(5000);
    digitalWrite(reset, LOW);
  }
}
