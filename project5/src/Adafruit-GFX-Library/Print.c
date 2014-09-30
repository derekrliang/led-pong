/*
 Print.cpp - Base class that provides print() and println()
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
 
 Modified 23 November 2006 by David A. Mellis
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//#include "Arduino.h"

#include "Print.h"

// Public Methods //////////////////////////////////////////////////////////////

void Print_constructor(Print *print) //must call
{
	print->write = 0;
	print->writeEx = &Print_writeEx;
	print->write_error = 0;
}

int Print_getWriteError(Print *print) { return print->write_error; }
void Print_clearWriteError(Print *print) { Print__setWriteError(print, 0); }
void Print__setWriteError(Print *print, int err/* = 1*/) { print->write_error = err; }

/* default implementation: may be overridden */
size_t Print_write(Print *print, const char *str) {
	if (str == NULL) return 0;
	return Print_writeEx(print, (const uint8_t *)str, strlen(str));
}

size_t Print_writeEx(Print *print, const uint8_t *buffer, size_t size)
{
  size_t n = 0;
  while (size--) {
    n += print->write(print, *buffer++);
  }
  return n;
}

/*
size_t Print_print0(Print *print, const __FlashStringHelper *ifsh)
{
  const char PROGMEM *p = (const char PROGMEM *)ifsh;
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    n += print->write(print, c);
  }
  return n;
}*/

/*
size_t Print_print1(Print *print, const String &s)
{
  size_t n = 0;
  for (uint16_t i = 0; i < s.length(); i++) {
    n += print->write(print, s[i]);
  }
  return n;
}*/

size_t Print_print2(Print *print, const char str[])
{
  return Print_write(print, str);
}

size_t Print_print3(Print *print, char c)
{
  return print->write(print, c);
}

size_t Print_print4(Print *print, unsigned char b, int base)
{
  return Print_print8(print, (unsigned long) b, base);
}

size_t Print_print5(Print *print, int n, int base)
{
  return Print_print7(print, (long) n, base);
}

size_t Print_print6(Print *print, unsigned int n, int base)
{
  return Print_print8(print, (unsigned long) n, base);
}

size_t Print_print7(Print *print, long n, int base)
{
  if (base == 0) {
    return print->write(print, n);
  } else if (base == 10) {
    if (n < 0) {
      int t = Print_print3(print, '-');
      n = -n;
      return Print__printNumber(print, n, 10) + t;
    }
    return Print__printNumber(print, n, 10);
  } else {
    return Print__printNumber(print, n, base);
  }
}

size_t Print_print8(Print *print, unsigned long n, int base)
{
  if (base == 0) return print->write(print, n);
  else return Print__printNumber(print, n, base);
}

size_t Print_print9(Print *print, double n, int digits)
{
  return Print__printFloat(print, n, digits);
}

/*
size_t Print_println(Print *print, const __FlashStringHelper *ifsh)
{
  size_t n = Print_print0(print, ifsh);
  n += Print_println(print);
  return n;
}*/

/*
size_t Print_print10(Print *print, const Printable& x)
{
  return x.printTo(*this);
}*/

size_t Print_println11(Print *print)
{
  size_t n = Print_print3(print, '\r');
  n += Print_print3(print, '\n');
  return n;
}

/*
size_t Print_println(Print *print, const String &s)
{
  size_t n = Print_print1(print, s);
  n += Print_println(print);
  return n;
}*/

size_t Print_println2(Print *print, const char c[])
{
  size_t n = Print_print2(print, c);
  n += Print_println11(print);
  return n;
}

size_t Print_println3(Print *print, char c)
{
  size_t n = Print_print3(print, c);
  n += Print_println11(print);
  return n;
}

size_t Print_println4(Print *print, unsigned char b, int base)
{
  size_t n = Print_print4(print, b, base);
  n += Print_println11(print);
  return n;
}

size_t Print_println5(Print *print, int num, int base)
{
  size_t n = Print_print5(print, num, base);
  n += Print_println11(print);
  return n;
}

size_t Print_println6(Print *print, unsigned int num, int base)
{
  size_t n = Print_print6(print, num, base);
  n += Print_println11(print);
  return n;
}

size_t Print_println7(Print *print, long num, int base)
{
  size_t n = Print_print7(print, num, base);
  n += Print_println11(print);
  return n;
}

size_t Print_println8(Print *print, unsigned long num, int base)
{
  size_t n = Print_print8(print, num, base);
  n += Print_println11(print);
  return n;
}

size_t Print_println9(Print *print, double num, int digits)
{
  size_t n = Print_print9(print, num, digits);
  n += Print_println11(print);
  return n;
}

/*
size_t Print_println10(Print *print, const Printable& x)
{
  size_t n = Print_print10(print, x);
  n += Print_println11(print);
  return n;
}*/

// Private Methods /////////////////////////////////////////////////////////////

size_t Print__printNumber(Print *print, unsigned long n, uint8_t base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  // prevent crash if called with base == 1
  if (base < 2) base = 10;

  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while(n);

  return Print_write(print, str);
}

size_t Print__printFloat(Print *print, double number, uint8_t digits) 
{ 
  size_t n = 0;
  
  if (isnan(number)) return Print_print2(print, "nan");
  if (isinf(number)) return Print_print2(print, "inf");
  if (number > 4294967040.0) return Print_print2 (print, "ovf");  // constant determined empirically
  if (number <-4294967040.0) return Print_print2 (print, "ovf");  // constant determined empirically
  
  // Handle negative numbers
  if (number < 0.0)
  {
     n += Print_print3(print, '-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  n += Print_print8(print, int_part, 2);//TODO: verify behavior of using third arg 2

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += Print_print2(print, "."); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = (int)(remainder);
    n += Print_print5(print, toPrint, DEC); //TODO: verify third argument behavior
    remainder -= toPrint; 
  } 
  
  return n;
}