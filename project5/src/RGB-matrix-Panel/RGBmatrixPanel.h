#if ARDUINO >= 100
 #include "Arduino.h"
#elif defined(ARDUINO)
 #include "WProgram.h"
 #include "pins_arduino.h"
#else
 #include "pins_atmega32.h"
#endif
#include "../Adafruit-GFX-Library/Adafruit_GFX.h"

#ifndef RGBMATRIXPANEL_H_
#define RGBMATRIXPANEL_H_

typedef struct _RGBmatrixPanel {
  Adafruit_GFX agfx;
  // Printing
  uint8_t *_matrixbuff[2];
  uint8_t _nRows, _nPlanes, _backindex;
  uint8_t _swapflag;


  // PORT register pointers, pin bitmasks, pin numbers:
  volatile uint8_t
    *_latport, *_oeport, *_addraport, *_addrbport, *_addrcport, *_addrdport;
  uint8_t
    _sclkpin, _latpin, _oepin, _addrapin, _addrbpin, _addrcpin, _addrdpin,
    _sclk, _latch, _oe, _a, _b, _c, _d;

  // Counters/pointers for interrupt handler:
  volatile uint8_t _row, _plane;
  volatile uint8_t *_buffptr;
} RGBmatrixPanel;

// Init/alloc code common to both constructors:
void RGBmatrixPanel_init(RGBmatrixPanel *rgbmp, uint8_t rows, uint8_t a, uint8_t b, uint8_t c,
uint8_t sclk, uint8_t latch, uint8_t oe, uint8_t dbuf);

// Constructor for 16x32 panel:
void RGBmatrixPanel_Constructor_16x32(RGBmatrixPanel *rgbmp, uint8_t a, uint8_t b, uint8_t c,
uint8_t sclk, uint8_t latch, uint8_t oe, uint8_t dbuf);

// Constructor for 32x32 panel (adds 'd' pin):
void RGBmatrixPanel_Constructor_32x32(RGBmatrixPanel *rgbmp, uint8_t a, uint8_t b, uint8_t c, uint8_t d,
uint8_t sclk, uint8_t latch, uint8_t oe, uint8_t dbuf);

void RGBmatrixPanel_begin(RGBmatrixPanel *rgbmp);
void RGBmatrixPanel_drawPixel(Adafruit_GFX *agfx, int16_t x, int16_t y, uint16_t c); //override
void RGBmatrixPanel_invertDisplay(Adafruit_GFX *agfx, uint8_t i); //override
void RGBmatrixPanel_fillScreen(Adafruit_GFX *agfx, uint16_t c); //override
void RGBmatrixPanel_updateDisplay(RGBmatrixPanel *rgbmp);
void RGBmatrixPanel_swapBuffers(RGBmatrixPanel *rgbmp, uint8_t);
void RGBmatrixPanel_dumpMatrix(RGBmatrixPanel *rgbmp);
uint8_t *RGBmatrixPanel_backBuffer(RGBmatrixPanel *rgbmp);
uint16_t RGBmatrixPanel_Color333(RGBmatrixPanel *rgbmp, uint8_t r, uint8_t g, uint8_t b);
uint16_t RGBmatrixPanel_Color444(RGBmatrixPanel *rgbmp, uint8_t r, uint8_t g, uint8_t b);
uint16_t RGBmatrixPanel_Color888(RGBmatrixPanel *rgbmp, uint8_t r, uint8_t g, uint8_t b);
uint16_t RGBmatrixPanel_Color888Ex(RGBmatrixPanel *rgbmp, uint8_t r, uint8_t g, uint8_t b, uint8_t gflag);
uint16_t RGBmatrixPanel_ColorHSV(RGBmatrixPanel *rgbmp, long hue, uint8_t sat, uint8_t val, uint8_t gflag);

#endif /* RGBMATRIXPANEL_H_ */