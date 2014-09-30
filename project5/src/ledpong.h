/*
 * ledpong.h
 *
 * Created: 6/2/2013 10:06:22 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#include "RGB-matrix-Panel/RGBmatrixPanel.h" // Hardware-specific library
#include "ball.h"
#include "paddle.h"
#include "score.h"
#include "nesctrlr.h"
#include "keypad.h"
#include "coin.h"

#ifndef LEDPONG_H_
#define LEDPONG_H_

//these are the API#s see pins_atmega32.h for the mapping PIN#->API#
#define CLK 18
#define OE  19
#define LAT 20
#define A   21
#define B   22
#define C   23

#define PLAYER_1 0
#define PLAYER_2 1

typedef struct _LEDPong
{
	RGBmatrixPanel matrix;
	Score score[2];
	Keypad keypad; 
	NESController gamepad1;
	NESController gamepad2;
	Ball ball;
	Paddle paddle1;
	Paddle paddle2;
	Coin coin;
	char had_collision;
	enum PlayStates {PS_BOOT, PS_PAYME, PS_PLAYING, PS_WIN, PS_CREDITS} _playStates;
} LEDPong;

void ledpong_renderScores(LEDPong *ledpong);
void ledpong_resetScore(LEDPong *ledpong);
void ledpong_init(LEDPong *ledpong);
void ledpong_step(LEDPong *ledpong);
void ledpong_render(LEDPong *ledpong);

typedef struct _Art {
	unsigned int 	 width;
	unsigned int 	 height;
	unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
	unsigned char	 pixel_data[32 * 16 * 3 + 1];
} Art;

void ledpong_drawArt(LEDPong *ledpong, Art *art);
void ledpong_resetPositions(LEDPong *ledpong);


void kp_ledpong_p1_paddle_move_left(void* data);
void kp_ledpong_p1_paddle_move_right(void* data);
void kp_ledpong_p2_paddle_move_left(void* data);
void kp_ledpong_p2_paddle_move_right(void* data);
void kp_ledpong_reset_score(void* data);

#endif /* LEDPONG_H_ */