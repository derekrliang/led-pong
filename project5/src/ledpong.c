/*
 * ledpong.c
 *
 * Created: 6/2/2013 10:06:12 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include <asf.h>
#include "ledpong.h"
#include "nesctrlr.h"
#include "ball.h"
#include "avr.h"
#include "main.h"
#include "music.h"
#include "coin.h"

int paidToPlay = 0;

/* GIMP RGB C-Source image dump (peteranteater.c) */

const Art image_peterAnteater PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+\0\0+\0\0"
	"+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0+\0\0+\0\0+\0\0+SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+SS\0SS\0SS\0\0\0+\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+SS\0SS\0\0\0+\0\0+SS\0\0\0+\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0+SS\0SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+\0"
	"\0+SS\0\0\0+SS\0\0\0+\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+"
	"\0\0+\0\0\0\0\0\0\0\0\0\0\0+SS\0SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0\0\0+\0\0+\0\0"
	"+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0\0\0+\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+SS\0SS\0SS\0SS\0SS\0\0\0+SS\0"
	"\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0SS\0SS\0\0"
	"\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+SS\0\0\0+\0\0+SS\0SS\0S"
	"S\0SS\0SS\0\0\0+\0\0\0\0\0+\0\0\0\0\0+\0\0\0\0\0\0\0\0+\0\0\0\0\0+SS\0SS"
	"\0SS\0SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+SS\0\0\0+\0\0"
	"+SS\0SS\0SS\0SS\0SS\0\0\0+\0\0+\0\0\0\0\0+\0\0\0\0\0+\0\0\0\0\0+\0\0+\0\0"
	"\0\0\0+SS\0SS\0SS\0SS\0\0\0+\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+\0\0+"
	"SS\0SS\0SS\0SS\0SS\0SS\0\0\0+\0\0+\0\0+\0\0+\0\0\0\0\0+\0\0\0\0\0+\0\0\0"
	"\0\0+\0\0+\0\0\0\0\0+SS\0SS\0\0\0+\0\0+\0\0+\0\0\0\0\0\0\0\0\0\0\0+\0\0+"
	"\0\0+SS\0SS\0SS\0SS\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0\0\0+\0\0\0\0\0\0"
	"\0\0\0\0\0+\0\0\0\0\0\0\0\0+\0\0\0\0\0+SS\0SS\0SS\0\0\0+\0\0+\0\0\0\0\0\0"
	"\0\0\0\0\0+SS\0SS\0SS\0SS\0\0\0+\0\0+\0\0+\0\0\0\0\0+SS\0SS\0\0\0+SS\0\0"
	"\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0\0\0+\0"
	"\0+\0\0\0\0\0+\0\0+SS\0SS\0\0\0+\0\0+\0\0+\0\0\0\0\0\0\0\0+\0\0+SS\0\0\0"
	"+\0\0+\0\0+SS\0SS\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0\0\0+SS\0S"
	"S\0SS\0\0\0+\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"+SS\0\0\0+\0\0+\0\0+SS\0SS\0SS\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0\0"
	"\0+\0\0+SS\0SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0\0\0\0+\0\0+\0\0+\0\0+\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+SS\0SS\0SS\0\0\0+\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+\0\0+\0\0+\0\0\0\0\0+\0\0+\0\0+\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0+SS\0SS\0SS\0SS\0SS\0SS\0"
	"\0\0+\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+\0\0+",
};
	
const Art image_insertCoin PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0"
	"\0\0\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300\0\0\0\377\0\300\377\0\300"
	"\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0"
	"\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300\377\0\300"
	"\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\377\0\300"
	"\377\0\300\377\0\300\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0"
	"\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\377\0\300\0"
	"\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300"
	"\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0\377\0\300\377\0\300"
	"\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\377"
	"\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0\377\0\300\377"
	"\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0"
	"\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\0\0\0"
	"\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\377\0\300"
	"\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377"
	"\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\377\0\300\0\0"
	"\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0"
	"\0\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\377\0\300\377"
	"\0\300\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0"
	"\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377"
	"\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300"
	"\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0"
	"\0\0\0\0\377\0\300\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377"
	"\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0"
	"\0\0\377\0\300\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0"
	"\377\0\300\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300"
	"\377\0\300\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377\0"
	"\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};	

const Art image_winPlayer1 PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\0\0\0SS\0\377\352\0\377\352\0"
	"\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0SS"
	"\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\0\0\0SS\0"
	"\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0SS\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377"
	"\352\0\0\0\0SS\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0SS\0\0\0\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\377\352\0\0\0\0\0\0\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0\377\352\0\377\352\0\377\352\0\0\0\0\377\352\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\0\0\0\377\352\0\377\352\0SS\0\377"
	"\352\0\377\352\0\377\352\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0"
	"SS\0SS\0\377\352\0\377\352\0\377\352\0SS\0SS\0\0\0\0\377\352\0\377\352\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SS\0SS\0SS\0"
	"\377\352\0SS\0SS\0SS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SS\0SS\0\377\352\0SS\0SS\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0SS\0\377\352\0SS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0"
	"\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0\360\0\377"
	"\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0\0\0\0\0"
	"\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0"
	"\377\0\0\0\360\0\377\360\0\377\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\360\0\377"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0"
	"\0\0\0\0\0\0\0\0\360\0\377\360\0\377\0\0\0\360\0\377\0\0\0\360\0\377\360"
	"\0\377\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\0\0\0\0"
	"\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377"
	"\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\0\0\0\360\0\377\360"
	"\0\377\0\0\0\360\0\377\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0"
	"\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0"
	"\0\0\0",
};

const Art image_winPlayer2 PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\0\0\0SS\0\377\352\0\377\352\0"
	"\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0SS"
	"\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\0\0\0SS\0"
	"\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0SS\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377"
	"\352\0\0\0\0SS\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0SS\0\0\0\0\0\0\0\377\352\0\377\352\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\377\352\0\0\0\0\0\0\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\377\352\0\377\352\0\377\352\0\377\352\0\0\0\0\377\352\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\0\0\0\377\352\0\377\352\0SS\0\377"
	"\352\0\377\352\0\377\352\0SS\0\377\352\0\377\352\0\377\352\0\377\352\0\377"
	"\352\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377\352\0\377\352\0"
	"SS\0SS\0\377\352\0\377\352\0\377\352\0SS\0SS\0\0\0\0\377\352\0\377\352\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SS\0SS\0SS\0"
	"\377\352\0SS\0SS\0SS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0SS\0SS\0\377\352\0SS\0SS\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0SS\0\377\352\0SS\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0"
	"\377\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\377\352\0\377"
	"\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352\0\377\352"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\0\0\0\0\0\0\0"
	"\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0"
	"\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377"
	"\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\360\0"
	"\377\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360"
	"\0\377\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\0\0\0\360\0\377\0\0\0\0"
	"\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\360\0"
	"\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\0\0\0\360\0"
	"\377\0\0\0\360\0\377\360\0\377\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0\360"
	"\0\377\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\0"
	"\0\0\0\0\0\360\0\377\360\0\377\0\0\0\360\0\377\360\0\377\0\0\0\0\0\0\360"
	"\0\377\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360"
	"\0\377\360\0\377\0\0\0\0\0\0",
};

const Art image_credits PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\360"
	"\0\377\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\360\0\377"
	"\360\0\377\360\0\377\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0"
	"\0\0\360\0\377\360\0\377\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377\0"
	"\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0"
	"\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\360\0\377\360\0\377\0"
	"\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0"
	"\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377"
	"\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\360\0\377\360\0\377\360\0\377"
	"\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0"
	"\377\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\360\0\377\0\0\0\360\0"
	"\377\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0"
	"\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\0\0"
	"\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\360"
	"\0\377\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\0\0\0"
	"\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\360\0\377"
	"\0\0\0\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0\360"
	"\0\377\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\360\0\377\360\0\377\360\0\377\0"
	"\0\0\360\0\377\360\0\377\0\0\0\0\0\0\0\0\0\360\0\377\0\0\0\0\0\0\360\0\377"
	"\0\0\0\360\0\377\360\0\377\360\0\377\360\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0",
};

const Art image_orson PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377x\0\377"
	"x\0\377x\0\377\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377"
	"\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377"
	"\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0"
	"\0\0\0\0\0x\0\377\0\0\0x\0\377x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377x"
	"\0\377x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377\0\0\0\0\0\0x"
	"\0\377\0\0\0x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0x\0\377\0\0\0\0\0\0"
	"x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0"
	"x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0"
	"\377x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377"
	"x\0\377x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0x\0\377x\0\377x\0\377"
	"\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0\0"
	"\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377"
	"\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377"
	"\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0"
	"\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377"
	"\0\0\0x\0\377x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377"
	"x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0"
	"\0\0x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0"
	"\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0"
	"x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0"
	"\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0"
	"\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0"
	"x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377\0"
	"\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0x\0\377x\0"
	"\377x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377x\0\377x\0\377\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};

const Art image_derek PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"x\0\377x\0\377\0\0\0\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377x\0\377"
	"x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x"
	"\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0"
	"x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0"
	"\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0"
	"\0\0x\0\377x\0\377x\0\377\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377x"
	"\0\377x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377"
	"\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0"
	"\0\0\0\0x\0\377\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0x\0\377x\0\377x\0\377\0\0"
	"\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0x\0\377"
	"\0\0\0\0\0\0x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0"
	"\377x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0"
	"\0x\0\377x\0\377x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0"
	"\0x\0\377\0\0\0\0\0\0x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0"
	"\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0"
	"\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0"
	"x\0\377\0\0\0\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0\0\0\0x\0\377\0\0\0"
	"x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0\0x\0\377x\0\377x\0\377\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0x\0\377\0\0"
	"\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377\0\0\0\0\0\0x\0\377"
	"x\0\377\0\0\0x\0\377\0\0\0\0\0\0\0\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0x\0\377x\0\377x\0\377x\0\377\0\0\0x\0\377\0\0\0x\0\377\0\0"
	"\0\0\0\0\0\0\0\0\0\0x\0\377\0\0\0x\0\377\0\0\0\0\0\0x\0\377x\0\377\0\0\0"
	"x\0\377x\0\377x\0\377x\0\377x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0x\0\377\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0",
};

const Art image_titleScreen PROGMEM = {
	32, 16, 3,
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\377"
	"\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300\377\0\300\377"
	"\0\300\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300\377"
	"\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300"
	"\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300"
	"\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377"
	"\0\300\377\0\300\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0"
	"\300\377\0\300\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377"
	"\0\300\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\377\0\300\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0"
	"\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300\377\0\300\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300\377"
	"\0\300\377\0\300\377\0\300\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300"
	"\0\0\0\0\0\0\377\0\300\377\0\300\377\0\300\377\0\300\0\0\0\0\0\0\377\0\300"
	"\377\0\300\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\204"
	"\377*\204\377*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204"
	"\377*\204\377*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204"
	"\377*\0\0\0\0\0\0\204\377*\204\377*\0\0\0\0\0\0\204\377*\204\377*\204\377"
	"*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204\377*\204\377*\204\377*\204\377"
	"*\0\0\0\0\0\0\204\377*\204\377*\204\377*\204\377*\204\377*\204\377*\0\0\0"
	"\0\0\0\0\0\0\204\377*\204\377*\204\377*\0\0\0\0\0\0\204\377*\204\377*\0\0"
	"\0\0\0\0\204\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204"
	"\377*\0\0\0\204\377*\204\377*\0\0\0\0\0\0\204\377*\204\377*\204\377*\204"
	"\377*\204\377*\204\377*\204\377*\0\0\0\0\0\0\204\377*\0\0\0\204\377*\0\0"
	"\0\0\0\0\204\377*\0\0\0\0\0\0\204\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\204"
	"\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\204\377*\0\0\0\204\377*\204\377*\204"
	"\377*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\0\0\0\0\0\0\204\377*\0\0\0\204"
	"\377*\204\377*\0\0\0\204\377*\0\0\0\0\0\0\204\377*\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\204\377*\204\377*\204\377*\0\0\0\0\0\0\204\377*\204\377*\0\0\0\204"
	"\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204\377*\0\0\0\204"
	"\377*\0\0\0\204\377*\204\377*\0\0\0\204\377*\0\0\0\204\377*\204\377*\0\0"
	"\0\204\377*\204\377*\204\377*\0\0\0\204\377*\204\377*\204\377*\204\377*\204"
	"\377*\204\377*\204\377*\0\0\0\204\377*\204\377*\204\377*\0\0\0\0\0\0\0\0"
	"\0\204\377*\204\377*\0\0\0\204\377*\204\377*\0\0\0\0\0\0\204\377*\0\0\0\204"
	"\377*\0\0\0\204\377*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\0\0\0\204\377*\204"
	"\377*\204\377*\204\377*\204\377*\204\377*\204\377*\0\0\0\204\377*\204\377"
	"*\204\377*\0\0\0\0\0\0\0\0\0\204\377*\204\377*\0\0\0\204\377*\0\0\0\0\0\0"
	"\0\0\0\204\377*\204\377*\204\377*\0\0\0\204\377*\0\0\0\0\0\0\0\0\0\204\377"
	"*\204\377*\0\0\0\204\377*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\204\377*\204\377*\204\377*\204\377*\204\377*\204\377*\204\377*\0\0"
	"\0\204\377*\204\377*\0\0\0\0\0\0\204\377*\204\377*\204\377*\0\0\0\204\377"
	"*\204\377*\204\377*\204\377*\204\377*\204\377*\204\377*\204\377*\204\377"
	"*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\204\377*\204\377*\204\377*\204"
	"\377*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\204\377*\0\0\0\0\0\0\204\377*\204"
	"\377*\204\377*\0\0\0\204\377*\204\377*\204\377*\204\377*\204\377*\204\377"
	"*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\204\377*\204\377*\204\377*\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"
	"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0",
};

void ledpong_drawArt(LEDPong *ledpong, Art *art)
{
	int p = 0;
	char c;
	uint8_t r,g,b;
	for (int y=0;y<=15;y++)
	for (int x=0;x<=31;x++) {
		r = pgm_read_byte(&(art->pixel_data[p++]));
		g = pgm_read_byte(&(art->pixel_data[p++]));
		b = pgm_read_byte(&(art->pixel_data[p++]));
		RGBmatrixPanel_drawPixel(&ledpong->matrix, x, y,
			RGBmatrixPanel_Color888(&ledpong->matrix, r, g, b));
	}
}

void ledpong_renderScores(LEDPong *ledpong)
{
	char buffer[80]="";
	sprintf(buffer, "%02u %02u", 
		score_getPoints(&ledpong->score[PLAYER_1]), score_getPoints(&ledpong->score[PLAYER_2]));
	Adafruit_GFX_setCursor(&ledpong->matrix.agfx.print, 2, 0);
	Adafruit_GFX_setTextColor(&ledpong->matrix.agfx, RGBmatrixPanel_Color333(&ledpong->matrix, 1, 0, 0));
	for(int i = 0;i<5;i++)
		Adafruit_GFX_write(&ledpong->matrix, buffer[i]);
}

void ledpong_resetScore(LEDPong *ledpong)
{
	ledpong->score[PLAYER_1] = 0;
	ledpong->score[PLAYER_2] = 0;
}

void kp_ledpong_p1_paddle_move_left(void* data)
{
	if (!paidToPlay)
		return;
	
	LEDPong* ledpong = (LEDPong*) data;
	ledpong->paddle1.y = --(ledpong->paddle1.y) > 2 ? ledpong->paddle1.y : 1;
}

void kp_ledpong_p1_paddle_move_right(void* data)
{
	if (!paidToPlay)
		return;

	LEDPong* ledpong = (LEDPong*) data;
	ledpong->paddle1.y = ++(ledpong->paddle1.y) < 14 ? ledpong->paddle1.y : 15-16/4;
}

void kp_ledpong_p2_paddle_move_left(void* data)
{
	if (!paidToPlay)
		return;

	LEDPong* ledpong = (LEDPong*) data;
	ledpong->paddle2.y = --(ledpong->paddle2.y) > 2 ? ledpong->paddle2.y : 1;
}

kp_ledpong_p2_paddle_move_right(void* data)
{
	if (!paidToPlay)
		return;
	
	LEDPong* ledpong = (LEDPong*) data;
	ledpong->paddle2.y = ++(ledpong->paddle2.y) < 14 ? ledpong->paddle2.y : 15-16/4;
}

void kp_ledpong_reset_score(void* data)
{
	LEDPong* ledpong = (LEDPong*) data;
	//ledpong_resetScore(ledpong);
}
volatile char pennies = 0;
void ledpong_init(LEDPong *ledpong)
{
	// *** LED PANEL INIT ***
	RGBmatrixPanel_Constructor_16x32(&ledpong->matrix, A, B, C, CLK, LAT, OE, 0);
	RGBmatrixPanel_begin(&ledpong->matrix);

	ledpong->_playStates = PS_BOOT;

	// *** CONTROLLER INIT ***
	nesctrlr_init();

	// *** MUSIC INIT ***
	music_init(&music);
	music_playSoundEffectBeep(&music); // MUSIC SOUND CHECK OK
	music_enable(&music);
	
	// *** COIN INIT ***
	coin_init();
	
	// *** KEYPAD INIT ***
	//keypad_init(&ledpong->keypad);
	//ledpong->keypad.data = ledpong;
	//ledpong->keypad.pressed1 = &kp_ledpong_p1_paddle_move_left;
	//ledpong->keypad.pressed2 = &kp_ledpong_p1_paddle_move_right;
	//ledpong->keypad.pressed4 = &kp_ledpong_p2_paddle_move_left;
	//ledpong->keypad.pressed5 = &kp_ledpong_p2_paddle_move_right;
	//ledpong->keypad.pressedC = &kp_ledpong_reset_score;
	

	// *** LEDPONG INIT ***
	ledpong_resetScore(ledpong);
	ledpong_resetPositions(ledpong);	
	ball_setColor(&ledpong->ball, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 1, 0));
	paddle_setExtent(&ledpong->paddle1, 2, 16/4);
	paddle_setExtent(&ledpong->paddle2, 2, 16/4);
	paddle_setColor(&ledpong->paddle1, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 7));
	paddle_setColor(&ledpong->paddle2, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 7));
	ball_randomVelocity(&ledpong->ball);
	ledpong->had_collision = 0;
	pennies = 0;
}

void ledpong_resetPositions(LEDPong *ledpong)
{
	ball_moveCenter(&ledpong->ball);
	paddle_setPosition(&ledpong->paddle1, 0, 16/2-1-16/4/2);
	paddle_setPosition(&ledpong->paddle2, 31-1, 16/2-1-16/4/2);
}

ISR(INT2_vect)
{
	pennies++;
	music_playSoundEffectBeep(&music); // MUSIC SOUND CHECK OK
}


int updateTick = 0;
void ledpong_step(LEDPong *ledpong)
{
	//get controller states
	wait_avr_ms(17); //we should call every 16.667ms //keep so ball doesn't move fast
	ledpong->gamepad1 = nesctrlr_pollPlayer1();
	ledpong->gamepad2 = nesctrlr_pollPlayer2();
	//nesctrlr_pollAll(&ledpong->gamepad1, &ledpong->gamepad2);
	//keypad_update(&ledpong->keypad);

	if (pennies >= 25) {
		paidToPlay = 1;
		//RGBmatrixPanel_drawPixel(&ledpong->matrix, 0, 0, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 7));
		pennies = 0;
		ledpong->_playStates = PS_PLAYING;
		ledpong_resetPositions(&ledpong);
		ball_randomVelocity(&ledpong->ball);
	}	

	/*
	if (ledpong->gamepad1 & NES_BUTTON_P1_A)
		//RGBmatrixPanel_drawPixel(&ledpong->matrix, 0, 0, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 7));
	if (ledpong->gamepad1 & NES_BUTTON_P1_B)
		//RGBmatrixPanel_drawPixel(&ledpong->matrix, 1, 0, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 7, 0));
	if (ledpong->gamepad1 & NES_BUTTON_P1_SELECT)
		//RGBmatrixPanel_drawPixel(&ledpong->matrix, 2, 0, RGBmatrixPanel_Color333(&ledpong->matrix, 7, 0, 0));
	if (ledpong->gamepad1 & NES_BUTTON_P1_START)
		//RGBmatrixPanel_drawPixel(&ledpong->matrix, 3, 0, RGBmatrixPanel_Color333(&ledpong->matrix, 7, 7, 7));
	*/
		
	if (ledpong->gamepad1 & NES_BUTTON_P1_UP)
		kp_ledpong_p1_paddle_move_left(ledpong);
	if (ledpong->gamepad1 & NES_BUTTON_P1_DOWN)
		kp_ledpong_p1_paddle_move_right(ledpong);
	if (ledpong->gamepad1 & NES_BUTTON_P1_LEFT)
		kp_ledpong_p1_paddle_move_left(ledpong);
	if (ledpong->gamepad1 & NES_BUTTON_P1_RIGHT)
		kp_ledpong_p1_paddle_move_right(ledpong);

	if (ledpong->gamepad2 & NES_BUTTON_P2_A) //bugged
		kp_ledpong_p2_paddle_move_left(ledpong);
	if (ledpong->gamepad2 & NES_BUTTON_P2_B) //bugged
		kp_ledpong_p2_paddle_move_right(ledpong);
	//if (ledpong->gamepad2 & NES_BUTTON_P2_SELECT) //bugged
	//	kp_ledpong_p2_paddle_move_left(ledpong);
	//if (ledpong->gamepad2 & NES_BUTTON_P2_START)
	//	kp_ledpong_p2_paddle_move_right(ledpong);

	//if (ledpong->gamepad2 & NES_BUTTON_P2_UP)
	//	kp_ledpong_p2_paddle_move_left(ledpong); 
	//if (ledpong->gamepad2 & NES_BUTTON_P2_DOWN)
	//	kp_ledpong_p2_paddle_move_right(ledpong);
	//if (ledpong->gamepad2 & NES_BUTTON_P2_LEFT)
	//	kp_ledpong_p2_paddle_move_left(ledpong);
	//if (ledpong->gamepad2 & NES_BUTTON_P2_RIGHT)
	//	kp_ledpong_p2_paddle_move_right(ledpong);

	if (ledpong->_playStates != PS_PLAYING)
		return;
	
	//move ball
//	if (updateTick % 2 == 0)
		ball_step(&ledpong->ball);
//	updateTick++;

	if (ledpong->had_collision)
	{
		music_playSoundEffectBeep(&music); // hit sound
		ledpong->had_collision = 0;
	}
	
	//check collisions
	if (ledpong->ball.x < 0) //ball went left out of board and reward point
	{
		score_awardPoint(&ledpong->score[PLAYER_2]);
		//play again
		ball_moveCenter(&ledpong->ball);
		ball_randomVelocity(&ledpong->ball);
	}
	
	if (ledpong->ball.x > 31) //ball went right out of board and reward point
	{
		score_awardPoint(&ledpong->score[PLAYER_1]);
		//play again
		ball_moveCenter(&ledpong->ball);
		ball_randomVelocity(&ledpong->ball);
	}
	
	if (score_getPoints(&ledpong->score[PLAYER_1]) == 10)
	{
		ledpong->_playStates = PS_WIN;
	}
	
	if (score_getPoints(&ledpong->score[PLAYER_2]) == 10)
	{
		ledpong->_playStates = PS_WIN;
	}		
	
	//ball hits top
	if (ledpong->ball.y <= 0)
	{
		ledpong->ball.speedY *= -1;
		ledpong->had_collision = 1;
	}
	
	//ball hits bottom wall
	if (ledpong->ball.y >= 15)
	{
		ledpong->ball.speedY *= -1;
		ledpong->had_collision = 1;
	}
	
	//ball hits left paddle
	if ((ledpong->ball.x >= ledpong->paddle1.x && ledpong->ball.x <= ledpong->paddle1.x + ledpong->paddle1.width ) &&
	ledpong->ball.y > ledpong->paddle1.y && ledpong->ball.y < (ledpong->paddle1.y + ledpong->paddle1.height))
	{
		ledpong->ball.speedX *= -1;
		ledpong->had_collision = 1;
	}
	
	//ball hits right paddle
	if ((ledpong->ball.x >= ledpong->paddle2.x && ledpong->ball.x <= ledpong->paddle2.x + ledpong->paddle2.width ) &&
	ledpong->ball.y > ledpong->paddle2.y && ledpong->ball.y < (ledpong->paddle2.y + ledpong->paddle2.height))
	{
		ledpong->ball.speedX *= -1;
		ledpong->had_collision = 1;
	}
}

int titleScreenState = 1;
int frames = 0;
void ledpong_render(LEDPong *ledpong)
{
	if (ledpong->_playStates == PS_BOOT)
	{
		RGBmatrixPanel_fillScreen(&ledpong->matrix, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 0));
		ledpong_drawArt(&ledpong->matrix, &image_peterAnteater);
		wait_avr_ms(2000);
		ledpong->_playStates = PS_PAYME;
	}
	if (ledpong->_playStates == PS_PAYME)
	{
		//ledpong_drawArt(&ledpong->matrix, &image_peterAnteater);
		if (paidToPlay == 0 && !(frames % 1000))
		{
			RGBmatrixPanel_fillScreen(&ledpong->matrix, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 0));
			if (titleScreenState)
				ledpong_drawArt(&ledpong->matrix, &image_titleScreen);
			else
				ledpong_drawArt(&ledpong->matrix, &image_insertCoin);
			titleScreenState = !titleScreenState;
			wait_avr_ms(1000);
			//music_playNyanCat(&music);
			return;
		}
		frames++;
		
	}
	if (ledpong->_playStates == PS_PLAYING)
	{
		//paint background
		RGBmatrixPanel_fillScreen(&ledpong->matrix, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 0));

		//paint score
		ledpong_renderScores(ledpong);

		//paint paddles
		paddle_render(&ledpong->matrix, &ledpong->paddle1);
		paddle_render(&ledpong->matrix, &ledpong->paddle2);

		//paint ball
		ball_render(&ledpong->matrix, &ledpong->ball);
	}
	if (ledpong->_playStates == PS_WIN)
	{
		if (score_getPoints(&ledpong->score[PLAYER_1]) == 10)
		{
			RGBmatrixPanel_fillScreen(&ledpong->matrix, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 0));
			ledpong_drawArt(&ledpong->matrix, &image_winPlayer1);
			music_playGreenSleeves(&music); // winning sound

		}
		else if (score_getPoints(&ledpong->score[PLAYER_2]) == 10)
		{
			RGBmatrixPanel_fillScreen(&ledpong->matrix, RGBmatrixPanel_Color333(&ledpong->matrix, 0, 0, 0));
			ledpong_drawArt(&ledpong->matrix, &image_winPlayer2);
			music_playGreenSleeves(&music); // winning sound
		}
		ledpong_drawArt(&ledpong->matrix, &image_credits);
		wait_avr_ms(2000);
		ledpong_drawArt(&ledpong->matrix, &image_orson);
		wait_avr_ms(2000);
		ledpong_drawArt(&ledpong->matrix, &image_derek);
		wait_avr_ms(2000);
		paidToPlay = 0;
		pennies = 0;
		ledpong_resetScore(ledpong);
		ledpong->_playStates = PS_PAYME;
	}
}
