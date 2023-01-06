#include <Colors.h>
#include <RGBmatrixPanel.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Pins.h>
class Display
{
private:
    RGBmatrixPanel matrix = RGBmatrixPanel(A, B, C, D, CLK, LAT, OE, false, 64);

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

public:
    Display(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t clk, uint8_t lat, uint8_t oe);
    ~Display();

    void begin();
    void noBalls();
    void waitingStart();
    void showScore(int x, int y, String score, uint16_t color);
    void tilted();
};

Display::Display(uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t clk, uint8_t lat, uint8_t oe)
{
    // this->matrix = RGBmatrixPanel(A, B, C, D, clk, lat, oe, false, 64);
}

void Display::begin()
{
    this->matrix.begin();
    this->matrix.fillScreen(BLACK);
    this->matrix.setTextWrap(false);
    this->matrix.setFont(&FreeSans9pt7b);
    this->matrix.setTextSize(1);
}

void Display::noBalls()
{
}

void Display::showScore(int x, int y, String score, uint16_t color)
{
    this->matrix.setTextColor(color, BLACK);
    this->matrix.setCursor(x, y);
    this->matrix.print(score.substring(0, 3));
    this->matrix.drawPixel(x + 18, y + 6, color);
    this->matrix.setCursor(x + 20, y);
    this->matrix.print(score.substring(3, 6));
    this->matrix.drawPixel(x + 38, y + 6, color);
    this->matrix.setCursor(x + 40, y);
    this->matrix.print(score.substring(6));
}

void Display::tilted()
{
    this->matrix.fillScreen(BLACK);
    this->matrix.setTextColor(RED, BLACK);
    this->matrix.setTextSize(1);
    this->matrix.setCursor(12, 2);
    this->matrix.print("Flipper");
    this->matrix.setCursor(12, 13);
    this->matrix.print("Bascul");
    this->matrix.drawChar(48, 13, 0x82, RED, BLACK, 1);
}