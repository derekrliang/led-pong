/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t

//#include "WString.h"
//#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

typedef struct _Print Print;
struct _Print
{
    int write_error;

	size_t (*write)(Print *print, uint8_t); //abstract must be defined
    size_t (*writeEx)(Print *print, const uint8_t *buffer, size_t size);
};

size_t Print_writeEx(Print *print, const uint8_t *buffer, size_t size);
size_t Print_write(Print *print, const char *str);

size_t Print__printNumber(Print *print, unsigned long, uint8_t);
size_t Print__printFloat(Print *print, double, uint8_t);

void Print__setWriteError(Print *print, int err/* = 1*/);

void Print_constructor(Print *print); //must call

int Print_getWriteError(Print *print);
void Print_clearWriteError(Print *print);

//size_t Print_print0(Print *print, const __FlashStringHelper *);
//size_t Print_print1(Print *print, const String &);
size_t Print_print2(Print *print, const char[]);
size_t Print_print3(Print *print, char);
size_t Print_print4(Print *print, unsigned char, int/* = DEC*/);
size_t Print_print5(Print *print, int, int/* = DEC*/);
size_t Print_print6(Print *print, unsigned int, int/* = DEC*/);
size_t Print_print7(Print *print, long, int/* = DEC*/);
size_t Print_print8(Print *print, unsigned long, int/* = DEC*/);
size_t Print_print9(Print *print, double, int/* = 2*/);
//size_t Print_print10(Print *print, const Printable&);

//size_t Print_println0(Print *print, const __FlashStringHelper *);
//size_t Print_println1(Print *print, const String &s);
size_t Print_println2(Print *print, const char[]);
size_t Print_println3(Print *print, char);
size_t Print_println4(Print *print, unsigned char, int/* = DEC*/);
size_t Print_println5(Print *print, int, int/* = DEC*/);
size_t Print_println6(Print *print, unsigned int, int/* = DEC*/);
size_t Print_println7(Print *print, long, int/* = DEC*/);
size_t Print_println8(Print *print, unsigned long, int/* = DEC*/);
size_t Print_println9(Print *print, double, int/* = 2*/);
//size_t Print_println10(Print *print, const Printable&);
size_t Print_println11(Print *print);

#endif