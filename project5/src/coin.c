/*
 * coin.c
 *
 * Created: 6/2/2013 9:44:36 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#include "avr.h"
#include "coin.h"
//information is vague because the seller doesn't give a datasheet
//manual
//http://www.adafruit.com/datasheets/CHmulticoin.jpg
//http://adafruit.com/forums/viewtopic.php?f=19&t=37935
//gray = counter (pulses differently for different coins)
//white = coin ()

//SWITCH
//NC PULSE ONLY THE COIN(WHITE) LINE
//NO PULSE BOTH THE COIN(WHITE) AND THE COUNT LINE (GREY)

//grey = gnd

void coin_init(void)
{
	//DDR
	CLR_BIT(COIN_ACCEPTOR_DDR, COIN_ACCEPTOR_PIN_COIN); //input
	//CLR_BIT(COIN_ACCEPTOR_DDR, COIN_ACCEPTOR_PIN_COUNT); //input
	
	//HARDWARE INTERRUPT ENABLE
	//SET_BIT(MCUCSR, ISC2); //DETECT RISING OR FALLING 0=FALLING 1=RISING
	CLR_BIT(MCUCSR, ISC2); //DETECT RISING OR FALLING 0=FALLING 1=RISING
	SET_BIT(GICR, 5); //IRQ2
	//SET_BIT(GIFR, INTF2); //CLEAR INTERRUPT
	sei();
}

