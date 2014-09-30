/*
 * pins_atmega32.c
 *
 * Created: 6/1/2013 9:45:33 AM
 *  Author: Orson Teodoro
 */ 

#include <asf.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include "pins_atmega32.h"

// Amtel ATmega32
//                          ___________
//              PB0     1  |           | 40    PA0
//              PB1     2  |           | 39    PA1
//              PB2     3  |           | 38    PA2
//              PB3     4  |           | 37    PA3
//              PB4     5  |           | 36    PA4
//              PB5     6  |           | 35    PA5
//              PB6     7  |           | 34    PA6
//              PB7     8  |           | 33    PA7
//              RST     9  |           | 32    ARF
//              VCC    10  |           | 31    GND
//              GND    11  |           | 30    AVC
//              XT2    12  |           | 29    PC7
//              XT1    13  |           | 28    PC6
//              PD0    14  |           | 27    PC5
//              PD1    15  |           | 26    PC4
//              PD2    16  |           | 25    PC3
//              PD3    17  |           | 24    PC2
//              PD4    18  |           | 23    PC1
//              PD5    19  |           | 22    PC0
//              PD6    20  |           | 21    PD7
//                          -----------

#define PA 1
#define PB 2
#define PC 3
#define PD 4

//#define __AVR_ATmega32__

//A{0,1,2,3} analog port pins
//original code was based on the Arduino Mega i think
//you can find the defines for the A{1,2,3,4,...,n} pins used in the examples
//https://android.googlesource.com/platform/external/arduino/+/tools_r21/hardware/arduino/cores/arduino/WProgram.h

//these tables are device dependent
//http://libelium.net/api/waspmote/pins__waspmote_8c-source.html
//const static uint8_t A0
#define NOT_A_PORT 0 //from pins_arduino.h

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
	PB, /* 0 */
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PB,
	PD, /* 8 */
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PD,
	PC, /* 16 */
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PC,
	PA, /* 24 */
	PA,
	PA,
	PA,
	PA,
	PA,
	PA,
	PA
};

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = {
	//  PIN                           PORT  PIN             API#      PIN#            DESCRIPTION
	_BV(0),                   //      PB    0               0         1
	_BV(1),                   //      PB    1               1         2
	_BV(2),                   //      PB    2               2         3
	_BV(3),                   //      PB    3               3         4
	_BV(4),                   //      PB    4               4         5
	_BV(5),                   //      PB    5               5         6
	_BV(6),                   //      PB    6               6         7
	_BV(7),                   //      PB    7               7         8
	_BV(0),                   //      PD    0               8         14
	_BV(1),                   //      PD    1               9         15
	_BV(2),                   //      PD    2               10        16
	_BV(3),                   //      PD    3               11        17
	_BV(4),                   //      PD    4               12        18
	_BV(5),                   //      PD    5               13        19
	_BV(6),                   //      PD    6               14        20
	_BV(7),                   //      PD    7               15        21
	_BV(0),                   //      PC    0               16        22
	_BV(1),                   //      PC    1               17        23
	_BV(2),                   //      PC    2               18        24
	_BV(3),                   //      PC    3               19        25
	_BV(4),                   //      PC    4               20        26
	_BV(5),                   //      PC    5               21        27
	_BV(6),                   //      PC    6               22        28
	_BV(7),                   //      PC    7               23        29
	_BV(7),                   //      PA    7               24        33
	_BV(6),                   //      PA    6               25        34
	_BV(5),                   //      PA    5               26        35
	_BV(4),                   //      PA    4               27        36
	_BV(3),                   //      PA    3               28        37
	_BV(2),                   //      PA    2               29        38
	_BV(1),                   //      PA    1               30        39
	_BV(0)                    //      PA    0               31        40
};

const uint16_t PROGMEM port_to_mode_PGM[] = {
	NOT_A_PORT,
	&DDRA,
	&DDRB,
	&DDRC,
	&DDRD
};

const uint16_t PROGMEM port_to_output_PGM[] = {
	NOT_A_PORT,
	&PORTA,
	&PORTB,
	&PORTC,
	&PORTD
};

//from arduino's wiring_digital.c
void pinMode(uint8_t pin, uint8_t mode)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *reg, *out;

	if (port == NOT_A_PIN) return;

	// JWS: can I let the optimizer do this?
	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (mode == INPUT) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out |= bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
		cli();
		*reg |= bit;
		SREG = oldSREG;
	}
}