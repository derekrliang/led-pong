/*
 * nesctrlr.h
 *
 * Created: 6/2/2013 9:38:37 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef NESCTRLR_H_
#define NESCTRLR_H_

#define NES_PLAYER_1 0
#define NES_PLAYER_2 1

//strange mappings

//player1
#define NES_BUTTON_P1_RIGHT		0x80
#define NES_BUTTON_P1_LEFT		0x40
#define NES_BUTTON_P1_DOWN		0x20
#define NES_BUTTON_P1_UP		0x10
#define NES_BUTTON_P1_START		0x08
#define NES_BUTTON_P1_SELECT	0x04
#define NES_BUTTON_P1_B			0x02
#define NES_BUTTON_P1_A			0x01

//player2
//#define NES_BUTTON_P2_UP		0x80
//#define NES_BUTTON_P2_START	0x40
//#define NES_BUTTON_P2_SELECT	0x20
#define NES_BUTTON_P2_B		0x10
#define NES_BUTTON_P2_A		0x08


#define NES_BUTTON_P2_RIGHT		0x80
#define NES_BUTTON_P2_LEFT		0x40
#define NES_BUTTON_P2_DOWN		0x20
#define NES_BUTTON_P2_UP		0x10
#define NES_BUTTON_P2_START		0x08
#define NES_BUTTON_P2_SELECT	0x04
//#define NES_BUTTON_P2_B			0x02
//#define NES_BUTTON_P2_A			0x01

#define NES_PLAYER_1_PORT PORTA
#define NES_PLAYER_1_PIN PINA
#define NES_PLAYER_1_DDR DDRA
#define NES_PLAYER_1_PIN_DATA 0
#define NES_PLAYER_1_PIN_LATCH 1
#define NES_PLAYER_1_PIN_PULSE 2

#define NES_PLAYER_2_PORT PORTA
#define NES_PLAYER_2_PIN PINA
#define NES_PLAYER_2_DDR DDRA
#define NES_PLAYER_2_PIN_DATA 3
#define NES_PLAYER_2_PIN_LATCH 4
#define NES_PLAYER_2_PIN_PULSE 5

typedef unsigned char NESController;

void nesctrlr_init();
NESController nesctrlr_pollPlayer1();
NESController nesctrlr_pollPlayer2();
void nesctrlr_pollAll(NESController *player1, NESController *player2);

#endif /* NESCTRLR_H_ */