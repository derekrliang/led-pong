/*
 * paddle.h
 *
 * Created: 6/2/2013 9:41:31 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef PADDLE_H_
#define PADDLE_H_

#include <stdint.h>
#include "RGB-matrix-Panel/RGBmatrixPanel.h" // Hardware-specific library


typedef struct _Paddle
{
	char x;
	char y;
	char width;
	char height;
	uint16_t color;
	char enabled;
	char visible;
} Paddle;

void paddle_setColor(Paddle *ball, uint16_t color);
uint16_t paddle_getColor(Paddle *ball);
void paddle_setExtent(Paddle *paddle, char w, char h);
void paddle_setPosition(Paddle *paddle, char x, char y);
char paddle_getPosition(Paddle *paddle, char *x, char *y);
void paddle_render(RGBmatrixPanel *matrix, Paddle *paddle);

#endif /* PADDLE_H_ */