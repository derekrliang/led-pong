#ifndef __avr__
#define __avr__

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/io.h>

#define XTAL_FRQ 8000000lu

#define SET_BIT(p,i) ((p) |=  (1 << (i)))
#define CLR_BIT(p,i) ((p) &= ~(1 << (i)))
#define GET_BIT(p,i) ((p) &   (1 << (i)))

#define WDR() asm volatile("wdr"::)
#define CLI() asm volatile("cli"::)
#define SEI() asm volatile("sei"::)
#define NOP() asm volatile("nop"::)
#define RST() for(;;);

void ini_avr(void);
void wait_avr_ms(unsigned short msec);
void wait_avr_us(unsigned short usec);
void wait_avr(unsigned short msec);

#endif