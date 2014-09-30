/******************************************************************
 This is the core graphics library for all our displays, providing
 basic graphics primitives (points, lines, circles, etc.). It needs
 to be paired with a hardware-specific library for each display
 device we carry (handling the lower-level functions).
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

#if ARDUINO >= 100
 #include "Arduino.h"
 #include "Print.h"
#else
 #include "Print.h"
 //#include "WProgram.h" //not applicable
#endif

#define swap(a, b) { int16_t t = a; a = b; b = t; }

typedef struct _Adafruit_GFX Adafruit_GFX;
struct _Adafruit_GFX  {
  Print print;
  int16_t  _WIDTH, _HEIGHT;   // this is the 'raw' display w/h - never changes
  int16_t  _width, _height; // dependent on rotation
  int16_t  _cursor_x, _cursor_y;
  uint16_t _textcolor, _textbgcolor;
  uint8_t  _textsize;
  uint8_t  _rotation;
  uint8_t  _wrap; // If set, 'wrap' text at right edge of display

  // this must be defined by the subclass
  void (*drawPixel)(Adafruit_GFX *agfx, int16_t x, int16_t y, uint16_t color);
  void (*invertDisplay)(Adafruit_GFX *agfx, uint8_t i);

  // these are 'generic' drawing functions, so we can share them!
  void (*drawLine)(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
  uint16_t color);
  void (*drawFastVLine)(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t h, uint16_t color);
  void (*drawFastHLine)(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, uint16_t color);
  void (*drawRect)(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color);
  void (*fillRect)(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, int16_t h,
  uint16_t color);
  void (*fillScreen)(Adafruit_GFX *agfx, uint16_t color);

  #if ARDUINO >= 100
  size_t (*write)(Adafruit_GFX *agfx, uint8_t);
  #else
  void   (*write)(Adafruit_GFX *agfx, uint8_t);
  #endif
};

// defaults
void Adafruit_GFX_drawLine(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
uint16_t color);
void Adafruit_GFX_drawFastVLine(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t h, uint16_t color);
void Adafruit_GFX_drawFastHLine(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, uint16_t color);
void Adafruit_GFX_drawRect(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, int16_t h,
uint16_t color);
void Adafruit_GFX_fillRect(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, int16_t h,
uint16_t color);
void Adafruit_GFX_fillScreen(Adafruit_GFX *agfx, uint16_t color);

//Adafruit_GFX();
// i have no idea why we have to formally call the constructor. kinda sux
void Adafruit_GFX_constructor(Adafruit_GFX *agfx, int16_t w, int16_t h);

void Adafruit_GFX_drawCircle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r, uint16_t color);
void Adafruit_GFX_drawCircleHelper(Adafruit_GFX *agfx, int16_t x0, int16_t y0,
int16_t r, uint8_t cornername, uint16_t color);
void Adafruit_GFX_fillCircle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r, uint16_t color);
void Adafruit_GFX_fillCircleHelper(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r,
uint8_t cornername, int16_t delta, uint16_t color);

void Adafruit_GFX_drawTriangle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
int16_t x2, int16_t y2, uint16_t color);
void Adafruit_GFX_fillTriangle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t x1, int16_t y1,
int16_t x2, int16_t y2, uint16_t color);
void Adafruit_GFX_drawRoundRect(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t w, int16_t h,
int16_t radius, uint16_t color);
void Adafruit_GFX_fillRoundRect(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t w, int16_t h,
int16_t radius, uint16_t color);

void Adafruit_GFX_drawBitmap(Adafruit_GFX *agfx, int16_t x, int16_t y,
const uint8_t *bitmap, int16_t w, int16_t h,
uint16_t color);
void Adafruit_GFX_drawChar(Adafruit_GFX *agfx, int16_t x, int16_t y, unsigned char c,
uint16_t color, uint16_t bg, uint8_t size);
#if ARDUINO >= 100
size_t Adafruit_GFX_write(Adafruit_GFX *agfx, uint8_t);
#else
void   Adafruit_GFX_write(Adafruit_GFX *agfx, uint8_t);
#endif
void Adafruit_GFX_setCursor(Adafruit_GFX *agfx, int16_t x, int16_t y);
void Adafruit_GFX_setTextColor(Adafruit_GFX *agfx, uint16_t c);
void Adafruit_GFX_setTextColorEx(Adafruit_GFX *agfx, uint16_t c, uint16_t bg);
void Adafruit_GFX_setTextSize(Adafruit_GFX *agfx, uint8_t s);
void Adafruit_GFX_setTextWrap(Adafruit_GFX *agfx, uint8_t w);

int16_t Adafruit_GFX_height(Adafruit_GFX *agfx);
int16_t Adafruit_GFX_width(Adafruit_GFX *agfx);

void Adafruit_GFX_setRotation(Adafruit_GFX *agfx, uint8_t r);
uint8_t Adafruit_GFX_getRotation(Adafruit_GFX *agfx);

void Adafruit_GFX_invertDisplay(Adafruit_GFX *agfx, uint8_t i);

#endif
