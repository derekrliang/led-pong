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

#include "Adafruit_GFX.h"
#include "glcdfont.c"
#include "Print.h"
#include <avr/pgmspace.h>
#include <stdlib.h>

void Adafruit_GFX_constructor(Adafruit_GFX *agfx, int16_t w, int16_t h) {
  Print_constructor(&agfx->print);
  agfx->_width = agfx->_WIDTH = w;
  agfx->_height = agfx->_HEIGHT = h;

  agfx->_rotation = 0;    
  agfx->_cursor_y = agfx->_cursor_x = 0;
  agfx->_textsize = 1;
  agfx->_textcolor = agfx->_textbgcolor = 0xFFFF;
  agfx->_wrap = 1;
  
  agfx->drawPixel = 0; //null
  agfx->invertDisplay = 0; //null
  
  agfx->drawLine = &Adafruit_GFX_drawLine;
  agfx->drawFastVLine = &Adafruit_GFX_drawFastVLine;
  agfx->drawFastHLine = &Adafruit_GFX_drawFastHLine;
  agfx->drawRect = &Adafruit_GFX_drawRect;
  agfx->fillRect = &Adafruit_GFX_fillRect;
  agfx->fillScreen = &Adafruit_GFX_fillScreen;
  agfx->write = &Adafruit_GFX_write;
}


// draw a circle outline
void Adafruit_GFX_drawCircle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r, 
			      uint16_t color) {
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  agfx->drawPixel(agfx, x0, y0+r, color);
  agfx->drawPixel(agfx, x0, y0-r, color);
  agfx->drawPixel(agfx, x0+r, y0, color);
  agfx->drawPixel(agfx, x0-r, y0, color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;
  
    agfx->drawPixel(agfx, x0 + x, y0 + y, color);
    agfx->drawPixel(agfx, x0 - x, y0 + y, color);
    agfx->drawPixel(agfx, x0 + x, y0 - y, color);
    agfx->drawPixel(agfx, x0 - x, y0 - y, color);
    agfx->drawPixel(agfx, x0 + y, y0 + x, color);
    agfx->drawPixel(agfx, x0 - y, y0 + x, color);
    agfx->drawPixel(agfx, x0 + y, y0 - x, color);
    agfx->drawPixel(agfx, x0 - y, y0 - x, color);
    
  }
}

void Adafruit_GFX_drawCircleHelper(Adafruit_GFX *agfx,  int16_t x0, int16_t y0,
               int16_t r, uint8_t cornername, uint16_t color) {
  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;
    if (cornername & 0x4) {
      agfx->drawPixel(agfx, x0 + x, y0 + y, color);
      agfx->drawPixel(agfx, x0 + y, y0 + x, color);
    } 
    if (cornername & 0x2) {
      agfx->drawPixel(agfx, x0 + x, y0 - y, color);
      agfx->drawPixel(agfx, x0 + y, y0 - x, color);
    }
    if (cornername & 0x8) {
      agfx->drawPixel(agfx, x0 - y, y0 + x, color);
      agfx->drawPixel(agfx, x0 - x, y0 + y, color);
    }
    if (cornername & 0x1) {
      agfx->drawPixel(agfx, x0 - y, y0 - x, color);
      agfx->drawPixel(agfx, x0 - x, y0 - y, color);
    }
  }
}

void Adafruit_GFX_fillCircle(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r, 
			      uint16_t color) {
  agfx->drawFastVLine(agfx, x0, y0-r, 2*r+1, color);
  Adafruit_GFX_fillCircleHelper(agfx, x0, y0, r, 3, 0, color);
}

// used to do circles and roundrects!
void Adafruit_GFX_fillCircleHelper(Adafruit_GFX *agfx, int16_t x0, int16_t y0, int16_t r,
				    uint8_t cornername, int16_t delta, uint16_t color) {

  int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
      agfx->drawFastVLine(agfx, x0+x, y0-y, 2*y+1+delta, color);
      agfx->drawFastVLine(agfx, x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
      agfx->drawFastVLine(agfx, x0-x, y0-y, 2*y+1+delta, color);
      agfx->drawFastVLine(agfx, x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

//----
// bresenham's algorithm - thx wikpedia
void Adafruit_GFX_drawLine(Adafruit_GFX *agfx, int16_t x0, int16_t y0, 
			    int16_t x1, int16_t y1, 
			    uint16_t color) {
  int16_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int16_t err = dx / 2;
  int16_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;
  }

  for (; x0<=x1; x0++) {
    if (steep) {
      agfx->drawPixel(agfx, y0, x0, color);
    } else {
      agfx->drawPixel(agfx, x0, y0, color);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


// draw a rectangle
void Adafruit_GFX_drawRect(Adafruit_GFX *agfx, int16_t x, int16_t y, 
			    int16_t w, int16_t h, 
			    uint16_t color) {
  agfx->drawFastHLine(agfx, x, y, w, color);
  agfx->drawFastHLine(agfx, x, y+h-1, w, color);
  agfx->drawFastVLine(agfx, x, y, h, color);
  agfx->drawFastVLine(agfx, x+w-1, y, h, color);
}

void Adafruit_GFX_drawFastVLine(Adafruit_GFX *agfx, int16_t x, int16_t y, 
				 int16_t h, uint16_t color) {
  // stupidest version - update in subclasses if desired!
  agfx->drawLine(agfx, x, y, x, y+h-1, color);
}


void Adafruit_GFX_drawFastHLine(Adafruit_GFX *agfx, int16_t x, int16_t y, 
				 int16_t w, uint16_t color) {
  // stupidest version - update in subclasses if desired!
  agfx->drawLine(agfx, x, y, x+w-1, y, color);
}

void Adafruit_GFX_fillRect(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w, int16_t h, 
			    uint16_t color) {
  // stupidest version - update in subclasses if desired!
  for (int16_t i=x; i<x+w; i++) {
    agfx->drawFastVLine(agfx, i, y, h, color); 
  }
}


void Adafruit_GFX_fillScreen(Adafruit_GFX *agfx, uint16_t color) {
  agfx->fillRect(agfx, 0, 0, agfx->_width, agfx->_height, color);
}
//----

// draw a rounded rectangle!
void Adafruit_GFX_drawRoundRect(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w,
  int16_t h, int16_t r, uint16_t color) {
  // smarter version
  agfx->drawFastHLine(agfx, x+r  , y    , w-2*r, color); // Top
  agfx->drawFastHLine(agfx, x+r  , y+h-1, w-2*r, color); // Bottom
  agfx->drawFastVLine(agfx,   x    , y+r  , h-2*r, color); // Left
  agfx->drawFastVLine(agfx,   x+w-1, y+r  , h-2*r, color); // Right
  // draw four corners
  Adafruit_GFX_drawCircleHelper(agfx, x+r    , y+r    , r, 1, color);
  Adafruit_GFX_drawCircleHelper(agfx, x+w-r-1, y+r    , r, 2, color);
  Adafruit_GFX_drawCircleHelper(agfx, x+w-r-1, y+h-r-1, r, 4, color);
  Adafruit_GFX_drawCircleHelper(agfx, x+r    , y+h-r-1, r, 8, color);
}

// fill a rounded rectangle!
void Adafruit_GFX_fillRoundRect(Adafruit_GFX *agfx, int16_t x, int16_t y, int16_t w,
				 int16_t h, int16_t r, uint16_t color) {
  // smarter version
  agfx->fillRect(agfx, x+r, y, w-2*r, h, color);

  // draw four corners
  Adafruit_GFX_fillCircleHelper(agfx, x+w-r-1, y+r, r, 1, h-2*r-1, color);
  Adafruit_GFX_fillCircleHelper(agfx, x+r    , y+r, r, 2, h-2*r-1, color);
}

// draw a triangle!
void Adafruit_GFX_drawTriangle(Adafruit_GFX *agfx, int16_t x0, int16_t y0,
				int16_t x1, int16_t y1, 
				int16_t x2, int16_t y2, uint16_t color) {
  agfx->drawLine(agfx, x0, y0, x1, y1, color);
  agfx->drawLine(agfx, x1, y1, x2, y2, color);
  agfx->drawLine(agfx, x2, y2, x0, y0, color);
}

// fill a triangle!
void Adafruit_GFX_fillTriangle (Adafruit_GFX *agfx,  int16_t x0, int16_t y0,
				  int16_t x1, int16_t y1, 
				  int16_t x2, int16_t y2, uint16_t color) {

  int16_t a, b, y, last;

  // Sort coordinates by Y order (y2 >= y1 >= y0)
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }
  if (y1 > y2) {
    swap(y2, y1); swap(x2, x1);
  }
  if (y0 > y1) {
    swap(y0, y1); swap(x0, x1);
  }

  if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
    a = b = x0;
    if(x1 < a)      a = x1;
    else if(x1 > b) b = x1;
    if(x2 < a)      a = x2;
    else if(x2 > b) b = x2;
    agfx->drawFastHLine(agfx, a, y0, b-a+1, color);
    return;
  }

  int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1,
    sa   = 0,
    sb   = 0;

  // For upper part of triangle, find scanline crossings for segments
  // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
  // is included here (and second loop will be skipped, avoiding a /0
  // error there), otherwise scanline y1 is skipped here and handled
  // in the second loop...which also avoids a /0 error here if y0=y1
  // (flat-topped triangle).
  if(y1 == y2) last = y1;   // Include y1 scanline
  else         last = y1-1; // Skip it

  for(y=y0; y<=last; y++) {
    a   = x0 + sa / dy01;
    b   = x0 + sb / dy02;
    sa += dx01;
    sb += dx02;
    /* longhand:
    a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    agfx->drawFastHLine(agfx, a, y, b-a+1, color);
  }

  // For lower part of triangle, find scanline crossings for segments
  // 0-2 and 1-2.  This loop is skipped if y1=y2.
  sa = dx12 * (y - y1);
  sb = dx02 * (y - y0);
  for(; y<=y2; y++) {
    a   = x1 + sa / dy12;
    b   = x0 + sb / dy02;
    sa += dx12;
    sb += dx02;
    /* longhand:
    a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
    b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
    */
    if(a > b) swap(a,b);
    agfx->drawFastHLine(agfx, a, y, b-a+1, color);
  }
}

void Adafruit_GFX_drawBitmap(Adafruit_GFX *agfx, int16_t x, int16_t y, 
			      const uint8_t *bitmap, int16_t w, int16_t h,
			      uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++ ) {
      if(pgm_read_byte(bitmap + j * byteWidth + i / 8) & (128 >> (i & 7))) {
	agfx->drawPixel(agfx, x+i, y+j, color);
      }
    }
  }
}


#if ARDUINO >= 100
size_t Adafruit_GFX_write(Adafruit_GFX *agfx, uint8_t c) {
#else
void Adafruit_GFX_write(Adafruit_GFX *agfx, uint8_t c) {
#endif
  if (c == '\n') {
    agfx->_cursor_y += agfx->_textsize*8;
    agfx->_cursor_x = 0;
  } else if (c == '\r') {
    // skip em
  } else {
    Adafruit_GFX_drawChar(agfx, agfx->_cursor_x, agfx->_cursor_y, c, agfx->_textcolor, agfx->_textbgcolor, agfx->_textsize);
    agfx->_cursor_x += agfx->_textsize*6;
    if (agfx->_wrap && (agfx->_cursor_x > (agfx->_width - agfx->_textsize*6))) {
      agfx->_cursor_y += agfx->_textsize*8;
      agfx->_cursor_x = 0;
    }
  }
#if ARDUINO >= 100
  return 1;
#endif
}

// draw a character
void Adafruit_GFX_drawChar(Adafruit_GFX *agfx, int16_t x, int16_t y, unsigned char c,
			    uint16_t color, uint16_t bg, uint8_t size) {

  if((x >= agfx->_width)            || // Clip right
     (y >= agfx->_height)           || // Clip bottom
     ((x + 5 * size - 1) < 0) || // Clip left
     ((y + 8 * size - 1) < 0))   // Clip top
    return;

  for (int8_t i=0; i<6; i++ ) {
    uint8_t line;
    if (i == 5) 
      line = 0x0;
    else 
      line = pgm_read_byte(font+(c*5)+i);
    for (int8_t j = 0; j<8; j++) {
      if (line & 0x1) {
        if (size == 1) // default size
          agfx->drawPixel(agfx, x+i, y+j, color);
        else {  // big size
          agfx->fillRect(agfx, x+(i*size), y+(j*size), size, size, color);
        } 
      } else if (bg != color) {
        if (size == 1) // default size
          agfx->drawPixel(agfx, x+i, y+j, bg);
        else {  // big size
          agfx->fillRect(agfx, x+i*size, y+j*size, size, size, bg);
        } 	
      }
      line >>= 1;
    }
  }
}

void Adafruit_GFX_setCursor(Adafruit_GFX *agfx, int16_t x, int16_t y) {
  agfx->_cursor_x = x;
  agfx->_cursor_y = y;
}


void Adafruit_GFX_setTextSize(Adafruit_GFX *agfx, uint8_t s) {
  agfx->_textsize = (s > 0) ? s : 1;
}


void Adafruit_GFX_setTextColor(Adafruit_GFX *agfx, uint16_t c) {
  agfx->_textcolor = c;
  agfx->_textbgcolor = c; 
  // for 'transparent' background, we'll set the bg 
  // to the same as fg instead of using a flag
}

 void Adafruit_GFX_setTextColorEx(Adafruit_GFX *agfx, uint16_t c, uint16_t b) {
   agfx->_textcolor = c;
   agfx->_textbgcolor = b; 
 }

void Adafruit_GFX_setTextWrap(Adafruit_GFX *agfx, uint8_t w) {
  agfx->_wrap = w;
}

uint8_t Adafruit_GFX_getRotation(Adafruit_GFX *agfx) {
  agfx->_rotation %= 4;
  return agfx->_rotation;
}

void Adafruit_GFX_setRotation(Adafruit_GFX *agfx, uint8_t x) {
  x %= 4;  // cant be higher than 3
  agfx->_rotation = x;
  switch (x) {
  case 0:
  case 2:
    agfx->_width = agfx->_WIDTH;
    agfx->_height = agfx->_HEIGHT;
    break;
  case 1:
  case 3:
    agfx->_width = agfx->_HEIGHT;
    agfx->_height = agfx->_WIDTH;
    break;
  }
}

void Adafruit_GFX_invertDisplay(Adafruit_GFX *agfx, uint8_t i) {
  // do nothing, can be subclassed
}


// return the size of the display which depends on the _rotation!
int16_t Adafruit_GFX_width(Adafruit_GFX *agfx) { 
  return agfx->_width; 
}
 
int16_t Adafruit_GFX_height(Adafruit_GFX *agfx) { 
  return agfx->_height; 
}
