/*
 * coin.h
 *
 * Created: 6/2/2013 9:44:46 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef COIN_H_
#define COIN_H_

typedef struct _Coin
{
	char _irq;
} Coin;

//number of pulses
#define COIN_NICKLE 5
#define COIN_DIME 10
#define COIN_QUARTER 25
#define COIN_HALF_DOLLAR 50

#define COIN_PULSE_FAST 20 //ms
#define COIN_PULSE_MEDIUM 50 //ms
#define COIN_PULSE_SLOW 100 //ms

#define COIN_ACCEPTOR_PIN PINB
#define COIN_ACCEPTOR_PORT PORTB
#define COIN_ACCEPTOR_DDR DDRB
#define COIN_ACCEPTOR_PIN_COIN 2  //DROP COIN GOES LOW WHEN COIN INSERTED AND PULSES SAME DURATION
#define COIN_ACCEPTOR_PIN_COUNT 1 //PULSES

void coin_init(void);

#endif /* COIN_H_ */