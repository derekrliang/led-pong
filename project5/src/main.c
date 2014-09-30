#include <asf.h>
#include "main.h"
#include "Adafruit-GFX-Library/Adafruit_GFX.h"   // Core graphics library
#include "RGB-matrix-Panel/RGBmatrixPanel.h" // Hardware-specific library
#include "avr.h"
#include "lcd.h"
#include "keypad.h"
#include "voltage.h"
#include "ledpong.h"
#include "music.h"


//TODO: USE VOLTAGE AS RNG SEED
// PORT D (BOTTOM LEFT)  : LED DATA
// D0  
// D1 
// D2 R1 3 16
// D3 G1 4 17
// D4 B1 5 18
// D5 R2 6 19
// D6 G2 7 20
// D7 B2 8 21
//
// PORT C (BOTTOM RIGHT) : LED CONTROL
// C0 
// C1 
// C2 CLK 24-17
// C3 OE 25-16
// C4 LATCH 26-15
// C5 ADDR A 27-14
// C6 ADDR B 28-13
// C7 ADDR C 29-12
//
// PORT A (TOP RIGHT) (NES CONTROLLERS)
// A0 CTRL1 DATA 40-1
// A1 CTRL1 LATCH 39-2
// A2 CTRL1 PULSE 38-3
// A3 CTRL2 DATA 
// A4 CTRL2 LATCH
// A5 CTRL2 PULSE
// A6
// A7
//
// PORT B (TOP LEFT) (SPEAKER)
// B0 
// B1 
// B2 
// B3 
// B4 SPEAKER OUT
// B5
// B6
// B7

volatile unsigned char flag;
Keypad keypad;
Voltage voltage;
LEDPong ledpong;
Music music;

void init_rng(void)
{
	//we need a seed.  there is no clock so we could use the a2d voltage and noise
	srand(19553);
}

int main(void)
{
	// *** TEST LEDPONG ***
	ledpong_init(&ledpong);
	
	for (;;)
	{
		ledpong_step(&ledpong);
		ledpong_render(&ledpong);
	}
}
