/*
 * nesctrlr.c
 *
 * Created: 6/2/2013 9:38:23 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include "nesctrlr.h"
#include "avr.h"

//see http://www.mit.edu/~tarvizo/nes-controller.html for timing/state diagram
//see http://cabalcontroller.blogspot.com/2010/04/interfacing-nes-controller-with-firefly.html for timing

void nesctrlr_init()
{
	//player 1
	SET_BIT(NES_PLAYER_1_DDR, 2); //output - clock
	SET_BIT(NES_PLAYER_1_DDR, 1); //output - latch
	CLR_BIT(NES_PLAYER_1_DDR, 0); //input - data

	//player 2
	SET_BIT(NES_PLAYER_2_DDR, 5); //output - clock
	SET_BIT(NES_PLAYER_2_DDR, 4); //output - latch
	CLR_BIT(NES_PLAYER_2_DDR, 3); //input - data
}

static inline void
sleep_12ns(void)
{
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
	NOP();NOP();NOP();NOP();NOP();NOP();NOP();NOP();
}
	//us timing specs
	//http://cabalcontroller.blogspot.com/2010/04/interfacing-nes-controller-with-firefly.html
	
	//state diagram
	//http://www.mit.edu/~tarvizo/nes-controller.html
	
	//vhdl implementation
	//http://web.mit.edu/6.111/www/s2004/PROJECTS/2/nes.htm
	//the vhdl example samples on the waits

void nesctrlr_pollAll(NESController *player1, NESController *player2)
{
	unsigned char state1 = 0, state2 = 0;

	CLR_BIT(PORTA, 2);
	CLR_BIT(PORTA, 5);
	
	SET_BIT(PORTA, 1);
	SET_BIT(PORTA, 4);
	sleep_12ns();
	CLR_BIT(PORTA, 1);
	CLR_BIT(PORTA, 4);
	
	for (int i=0;i<8;i++)
	{
		unsigned char b1 = GET_BIT(PINA, 0);
		unsigned char b2 = GET_BIT(PINA, 3);
		sleep_12ns();
		SET_BIT(PORTA, 2);
		SET_BIT(PORTA, 5);
		sleep_12ns();
		CLR_BIT(PORTA, 2);
		CLR_BIT(PORTA, 5);
		state1 |= b1 << i;
		state2 |= b2 << i;
	}

	*player1 = ~state1;
	*player2 = ~state2;
}


//call this every 16.1667ms
NESController nesctrlr_pollPlayer1()
{
	unsigned char state = 0;
	
	CLR_BIT(PORTA, 2);
	SET_BIT(PORTA, 1);
	sleep_12ns();
	CLR_BIT(PORTA, 1);
	
	for (int i=0;i<8;i++)
	{
		unsigned char b = GET_BIT(PINA, 0);
		sleep_12ns();
		SET_BIT(PORTA, 2);
		sleep_12ns();
		CLR_BIT(PORTA, 2);
		state |= b << i;
	}

	return ~state;
}

//call this every 16.1667ms
NESController nesctrlr_pollPlayer2()
{
	unsigned char state = 0;
	
	CLR_BIT(PORTA, 5);
	SET_BIT(PORTA, 4);
	sleep_12ns();
	CLR_BIT(PORTA, 4);
	
	for (int i=0;i<8;i++)
	{
		unsigned char b = GET_BIT(PINA, 3);
		sleep_12ns();
		SET_BIT(PORTA, 5);
		sleep_12ns();
		CLR_BIT(PORTA, 5);
		state |= b << i;
	}

	//unsigned char stateA = 0;
	//unsigned char stateB = 0;
	//stateA = state;
	//stateB = state;
	//state |= (~stateA) & 0xF8;
	//state |= stateB & 0x07;
	
	return state;
}
