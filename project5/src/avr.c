#include "avr.h"

void
ini_avr(void)
{
	//WDTCR = 15; //enable watch dog
}

//good tutorial on timers
//http://maxembedded.com/2011/06/22/introduction-to-avr-timers/

void
wait_avr_ms(unsigned short msec) //millisecond granularity
{
	TCCR0 = 3; //CLKio/64 = 125000Hz 
	//0.008ms per tick
	//125000 ticks 1 second
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.001); //125 ticks left //1ms per loop
		//TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.00001); //1 ticks left //0.008msms per loop
		SET_BIT(TIFR, TOV0); //enable overflow
		//WDR(); //reset watchdog
		while (!GET_BIT(TIFR, TOV0)); //wait till overflow
	}
	TCCR0 = 0; //stop timer
}

void
wait_avr_us(unsigned short usec) //microsecond granularity
{
	TCCR0 = 1; //CLKio/1 = 8000000Hz 
	//0.000000125s / 0.125us / 0.000125ms per tick
	//125000 ticks 1 second
	while (usec--) {
		TCNT0 = 256-8; //8 ticks left //1us per loop
		SET_BIT(TIFR, TOV0); //enable overflow
		//WDR(); //reset watchdog
		while (!GET_BIT(TIFR, TOV0)); //wait till overflow
	}
	TCCR0 = 0; //stop timer
}

void wait_avr(unsigned short msec) {wait_avr_ms(msec);} //backwards compat