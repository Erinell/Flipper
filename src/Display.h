#include <Arduino.h>
#include <RGBmatrixPanel.h>
#include "Settings.h"
#include "Colors.h"

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

void showVersion(RGBmatrixPanel display, int16_t x, int16_t y, uint16_t color)
{
    String str_version = VERSION;
    display.setFont();
    display.setCursor(x, y);
    display.setTextSize(1);
    display.setTextColor(color, BLACK);
    display.print(str_version.substring(0, 1));
    display.drawPixel(x + 5, y + 6, color);
    display.setCursor(x + 7, y);
    display.print(str_version.substring(2));
}

void showPlayersSelection(RGBmatrixPanel display, uint16_t color, String timer, String maxPlayer)
{
    display.setTextColor(color, BLACK);
    display.setTextSize(2);
    display.setCursor(27, 1);
    display.print(timer);
    display.setTextSize(1);
    display.setCursor(5, 20);
    display.print("Joueurs:");
    display.print(maxPlayer);
}

void showScore(RGBmatrixPanel display, int x, int y, unsigned long score, uint16_t color)
{
    display.setTextColor(color, BLACK);
#ifdef CENTER
    String str_score = (String)score;
    display.setCursor(32 - str_score.length() * 6 / 2, y);
    display.print(str_score);
#endif

#ifdef LEFT
    String str_score = (String)score;
    display.setCursor(x, y);
    display.print(str_score);
#endif

#ifdef RIGHT
    char _score[9];
    sprintf(_score, "%9lu", score);
    String str_score = _score;
    display.setCursor(x + 7, y);
    display.print(str_score);
#endif
}