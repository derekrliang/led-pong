/*
 * paddle.c
 *
 * Created: 6/2/2013 9:41:21 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include "paddle.h"
#include "ball.h"

void paddle_setColor(Paddle *ball, uint16_t color)
{
	ball->color = color;
}

uint16_t paddle_getColor(Paddle *ball)
{
	return ball->color;
}

void paddle_setExtent(Paddle *paddle, char w, char h)
{
	paddle->width = w;
	paddle->height = h;
}

void paddle_setPosition(Paddle *paddle, char x, char y)
{
	paddle->x = x;
	paddle->y = y;
}

char paddle_getPosition(Paddle *paddle, char *x, char *y)
{
	*x = paddle->x;
	*y = paddle->y;
}

void paddle_render(RGBmatrixPanel *matrix, Paddle *paddle)
{
	Adafruit_GFX_drawRect(matrix, paddle->x, paddle->y, paddle->width, paddle->height, paddle->color);
}

