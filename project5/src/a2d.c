/*
 * a2d.c
 *
 * Created: 6/1/2013 11:11:28 PM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include "a2d.h"
#include "avr.h"
#include "voltage.h"

void a2d_init(void)
{
	// IMPLICIT CLEAR OF ADMUX

	// STEP 1
	// CONFIGURE PIN TO READ BY MUX
	// MUX [0-4]
	// DEFAULT PIN ADC0

	// STEP 2
	// CONFIGURE BASE VOLTAGE TO COMPARE
	// 5V
	//CLR_BIT(ADMUX, 7); // USE AVCC AS BASE VOLTAGE
	SET_BIT(ADMUX, 6); // USE AVCC AS BASE VOLTAGE
	
	// STEP 3 SET ADLAR DATA REGISTER MODE
	
	// 2.5V
	// SET_BIT(ADMUX, 6); // USE AVCC AS BASE VOLTAGE
	// SET_BIT(ADMUX, 7); // USE AVCC AS BASE VOLTAGE
}

void a2d_start(void)
{
	SET_BIT(ADCSRA, 7); // ENABLE ADC
}

void a2d_stop(void)
{
	CLR_BIT(ADCSRA, 7); // DISABLE ADC
}

void a2d_read(void)
{
	SET_BIT(ADCSRA, 4); // INTERRUPT FLAG
	SET_BIT(ADCSRA, 6); // ADSC START CONVERSION
}

unsigned short a2d_result(void)
{
	while (!GET_BIT(ADCSRA, 4)); // WAIT
	return ADC;
}

unsigned short a2d_run(void)
{
	a2d_start();
	a2d_read();
	return a2d_result();
	//a2d_stop(); //DO NOT SET OR ELSE VOLTAGE READING IS NOT EXACTLY 0
}