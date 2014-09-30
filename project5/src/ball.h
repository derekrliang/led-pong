/*
 * ball.h
 *
 * Created: 6/2/2013 9:41:11 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef BALL_H_
#define BALL_H_

#include <stdint.h>
#include "RGB-matrix-Panel/RGBmatrixPanel.h" // Hardware-specific library

typedef struct _Ball
{
	char x;
	char y;
	uint16_t color;
	char speedX;
	char speedY;
	char enabled;
	char visible;
} Ball;

void ball_setColor(Ball *ball, uint16_t color);
uint16_t ball_getColor(Ball *ball);
void ball_setPosition(Ball *ball, char x, char y);
void ball_getPosition(Ball *ball, char *x, char *y);
void ball_moveCenter(Ball *ball);
void ball_randomVelocity(Ball *ball);
void ball_step(Ball *ball);
void ball_render(RGBmatrixPanel *matrix, Ball *ball);

#endif /* BALL_H_ */