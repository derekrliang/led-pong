/*
 * ball.c
 *
 * Created: 6/2/2013 9:41:00 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include <stdlib.h>
#include "ball.h"
#include "RGB-matrix-Panel/RGBmatrixPanel.h" // Hardware-specific library

void ball_setColor(Ball *ball, uint16_t color)
{
	ball->color = color;
}

uint16_t ball_getColor(Ball *ball)
{
	return ball->color;
}

void ball_setPosition(Ball *ball, char x, char y)
{
	ball->x = x;
	ball->y = y;
}

void ball_getPosition(Ball *ball, char *x, char *y)
{
	*x = ball->x;
	*y = ball->y;
}

//center ball on screen
void ball_moveCenter(Ball *ball)
{
	ball->x = 15;
	ball->y = 7;
}

void ball_randomVelocity(Ball *ball)
{
	ball->speedX = (rand() % 2+1) * (rand() % 2 ? 1 : -1);
	ball->speedY = (rand() % 2+1) * (rand() % 2 ? 1 : -1);
}

void ball_step(Ball *ball)
{
	ball->x += ball->speedX;
	ball->y += ball->speedY;
}

void ball_render(RGBmatrixPanel *matrix, Ball *ball)
{
	RGBmatrixPanel_drawPixel(matrix, ball->x, ball->y, ball->color);
}
