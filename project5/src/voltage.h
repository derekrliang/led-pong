/*
 * voltage.h
 *
 * Created: 6/1/2013 11:10:45 PM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef VOLTAGE_H_
#define VOLTAGE_H_

#define VOLTAGE_MAX_STORAGE 120

typedef struct _Voltage
{
	unsigned char enable;
	unsigned short instant;
	unsigned short max;
	unsigned short min;
	unsigned short avg;
	unsigned char _count;
	unsigned char _storeCurrent;
	unsigned short _store[VOLTAGE_MAX_STORAGE];
	unsigned long _sum;
} Voltage;

void voltage_enable(Voltage *voltage);
void voltage_disable(Voltage *voltage);
void voltage_lcd_clear(Voltage *voltage);
void voltage_clear(Voltage *voltage);
void voltage_parse_data(Voltage *voltage);
void voltage_print_data(Voltage *voltage);
void voltage_update(Voltage *voltage);

#endif /* VOLTAGE_H_ */