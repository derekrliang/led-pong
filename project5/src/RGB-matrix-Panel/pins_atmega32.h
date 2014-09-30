/*
 * pins_atmega32.h
 *
 * Created: 6/1/2013 9:46:09 AM
 *  Author: Orson Teodoro
 */ 


#ifndef PINS_ATMEGA32_H_
#define PINS_ATMEGA32_H_

#define _BV(bit) (1 << (bit)) //from sfr_defs.h: bit shift left
#define digitalPinToPort(P) ( pgm_read_byte( digital_pin_to_port_PGM + (P) ) ) //from Arduino.h
#define digitalPinToBitMask(P) ( pgm_read_byte( digital_pin_to_bit_mask_PGM + (P) ) ) //from Arduino.h
#define portOutputRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_output_PGM + (P))) ) //from Arduino.h
#define portModeRegister(P) ( (volatile uint8_t *)( pgm_read_word( port_to_mode_PGM + (P))) )

#define OUTPUT 1
#define INPUT 0
#define INPUT_PULLUP 2
#define 	NOT_A_PIN   0 //from pins_arduino.h

void pinMode(uint8_t pin, uint8_t mode);

extern const uint8_t digital_pin_to_port_PGM[];
extern const uint8_t digital_pin_to_bit_mask_PGM[];
extern const uint16_t port_to_mode_PGM[];
extern const uint16_t port_to_output_PGM[];

#endif /* PINS_ATMEGA32_H_ */