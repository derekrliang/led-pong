/*
 * keypad.c
 *
 * Created: 6/2/2013 9:40:09 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#include "keypad.h"
#include "avr.h"

static inline void
sleep_700ns(void)
{
	NOP();
	NOP();
	NOP();
}

void keypad_init(Keypad *keypad)
{
	// KEYPAD
	DDRA = 0x00;
	PORTA = 0x00;
	
	keypad->data = 0;
	keypad->_lastCol = -1;
	keypad->_lastRow = -1;
	
	keypad->pressed1 = 0;
	keypad->pressed2 = 0;
	keypad->pressed3 = 0;
	keypad->pressedA = 0;
	keypad->pressed4 = 0;
	keypad->pressed5 = 0;
	keypad->pressed6 = 0;
	keypad->pressedB = 0;
	keypad->pressed7 = 0;
	keypad->pressed8 = 0;
	keypad->pressed9 = 0;
	keypad->pressedC = 0;
	keypad->pressedAsterisk = 0;
	keypad->pressedOper0 = 0;
	keypad->pressedPound = 0;
	keypad->pressedD = 0;
}

int keypad_isKeyPressed(Keypad *keypad, int r, int c)
{
	// rows => pin 0 1 2 3
	// cols => pin 4 5 6 7
	
	if (keypad->_lastRow != r)
	{
		CLR_BIT(DDRA, 7 - keypad->_lastRow);
		CLR_BIT(PORTA, 7 - keypad->_lastRow);
		
		// STRONG 0
		SET_BIT(DDRA, 7 - r);
		CLR_BIT(PORTA, 7 - r);
		keypad->_lastRow = r;
	}
	
	if (keypad->_lastCol != c)
	{
		CLR_BIT(DDRA, 3 - keypad->_lastCol);
		CLR_BIT(PORTA, 3 - keypad->_lastCol);
		
		// WEAK 1
		CLR_BIT(DDRA, 3 - c);
		SET_BIT(PORTA, 3 - c);
		keypad->_lastCol = c;
	}
	
	// wait before checking bit for clearer readings
	//wait_avr(2);
	sleep_700ns();
	
	//GET 1/0 VALUE
	return GET_BIT(PINA, 3 - c) == 0;
}

int keypad_getKeycode(Keypad *keypad)
{
	for(int r = 0; r < 4; r++)
	{
		for(int c = 0; c < 4; c++)
		if (keypad_isKeyPressed(keypad, r, c))
			return (r * 4 + c + 1);
	}
	return 0;
}

void keypad_buttonAction(Keypad *keypad, char key)
{
	switch (key)
	{
		case 1: if (keypad->pressed1) keypad->pressed1(keypad->data); break;
		case 2: if (keypad->pressed2) keypad->pressed2(keypad->data); break;
		case 3: if (keypad->pressed3) keypad->pressed3(keypad->data); break;
		case 4: if (keypad->pressedA) keypad->pressedA(keypad->data); break;
		case 5: if (keypad->pressed4) keypad->pressed4(keypad->data); break;
		case 6: if (keypad->pressed5) keypad->pressed5(keypad->data); break;
		case 7: if (keypad->pressed6) keypad->pressed6(keypad->data); break;
		case 8: if (keypad->pressedB) keypad->pressedB(keypad->data); break;
		case 9: if (keypad->pressed7) keypad->pressed7(keypad->data); break;
		case 10: if (keypad->pressed8) keypad->pressed8(keypad->data); break;
		case 11: if (keypad->pressed9) keypad->pressed9(keypad->data); break;
		case 12: if (keypad->pressedC) keypad->pressedC(keypad->data); break;
		case 13: if (keypad->pressedAsterisk) keypad->pressedAsterisk(keypad->data); break;
		case 14: if (keypad->pressedOper0) keypad->pressedOper0(keypad->data); break;
		case 15: if (keypad->pressedPound) keypad->pressedPound(keypad->data); break;
		case 16: if (keypad->pressedD) keypad->pressedD(keypad->data); break;
	}
}

void keypad_update(Keypad *keypad) //run in a loop
{
	// check keypad also
	keypad->key = keypad_getKeycode(keypad);
	
	if (keypad->key == keypad->lastKey)
	{
		if (keypad_getKeycode(keypad) != keypad->key)
		return;
	}
	
	keypad_buttonAction(keypad, keypad->key);
	keypad->lastKey = keypad->key;
}