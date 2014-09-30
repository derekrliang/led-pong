/*
 * voltage.c
 *
 * Created: 6/1/2013 11:10:29 PM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#include <avr/pgmspace.h>
#include <stdio.h>
#include "voltage.h"
#include "a2d.h"
#include "lcd.h"

void voltage_enable(Voltage *voltage)
{
	voltage->enable = 1;
}

void voltage_disable(Voltage *voltage)
{
	voltage->enable = 0;
}

void voltage_lcd_clear(Voltage *voltage)
{
	clr_lcd();
	puts_lcd(PSTR("NOW:----AVG:----"));
	pos_lcd(1, 0);
	puts_lcd(PSTR("MAX:----MIN:----"));
}

void voltage_clear(Voltage *voltage)
{
	voltage->enable = 0;
	voltage->instant = 0;
	voltage->max = 0;
	voltage->min = 1025;
	voltage->avg = 0;
	voltage->_count = 0;
	voltage->_sum = 0;
	voltage->_storeCurrent = 0;
	voltage_lcd_clear(voltage);
}

void voltage_parse_data(Voltage *voltage)
{
	if (voltage->instant > voltage->max)
	voltage->max = voltage->instant;
	
	if (voltage->instant < voltage->min)
	voltage->min = voltage->instant;
	
	
	if (voltage->_storeCurrent >= VOLTAGE_MAX_STORAGE)
		voltage->_storeCurrent = 0;
	else
		voltage->_storeCurrent++;
	
	if (voltage->_count >= VOLTAGE_MAX_STORAGE)
		voltage->_sum -= voltage->_store[voltage->_storeCurrent];
	else
		voltage->_count++;
	
	voltage->_store[voltage->_storeCurrent] = voltage->instant;
	voltage->_sum += voltage->instant;
	
	voltage->avg = voltage->_sum / voltage->_count;
}

void voltage_print_data(Voltage *voltage)
{
	float volt_inst = (voltage->instant / 1024.0) * 5.0;
	float volt_max = (voltage->max / 1024.0) * 5.0;
	float volt_min = (voltage->min / 1024.0) * 5.0;
	float volt_avg = (voltage->avg / 1024.0) * 5.0;
	
	int volt_inst_dec_int = (volt_inst - (int) volt_inst) * 100;
	int volt_max_dec_int = (volt_max - (int) volt_max) * 100;
	int volt_min_dec_int = (volt_min - (int) volt_min) * 100;
	int volt_avg_dec_int = (volt_avg - (int) volt_avg) * 100;
	
	char topBuf[16];
	char botBuf[16];
	
	sprintf(topBuf, "NOW:%d.%02dAVG:%d.%02d", (int) volt_inst, volt_inst_dec_int, (int) volt_avg, volt_avg_dec_int);
	sprintf(botBuf, "MAX:%d.%02dMIN:%d.%02d", (int) volt_max, volt_max_dec_int, (int) volt_min, volt_min_dec_int);
	//sprintf(botBuf, "BCNT:%d CNT:%d", VOLTAGE_STORE_CURRENT, VOLTAGE_COUNT);
	
	clr_lcd();

	for (int i = 0; topBuf[i]; i++)
		put_lcd(topBuf[i]);
	
	pos_lcd(1, 0);
	
	for (int i = 0; botBuf[i]; i++)
		put_lcd(botBuf[i]);
}

void voltage_update(Voltage *voltage)
{
	if (voltage->enable)
	{
		// get data
		voltage->instant = a2d_run();
			
		// parse data
		voltage_parse_data(voltage);
			
		// output parsed data to LCD
		voltage_print_data(voltage);
	}			
}