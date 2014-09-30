/*
 * keypad.h
 *
 * Created: 6/2/2013 9:40:19 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

typedef struct _Keypad
{
	unsigned char key; //current key
	unsigned char lastKey;
	void *data;
	void (*pressed1) (void *data);
	void (*pressed2) (void *data);
	void (*pressed3) (void *data);
	void (*pressed4) (void *data);
	void (*pressed5) (void *data);
	void (*pressed6) (void *data);
	void (*pressed7) (void *data);
	void (*pressed8) (void *data);
	void (*pressed9) (void *data);
	void (*pressedA) (void *data);
	void (*pressedB) (void *data);
	void (*pressedC) (void *data);
	void (*pressedD) (void *data);
	void (*pressedAsterisk) (void *data);
	void (*pressedPound) (void *data);
	void (*pressedOper0) (void *data);
	int _lastRow;
	int _lastCol;
} Keypad;

void keypad_init(Keypad *keypad);
int keypad_isKeyPressed(Keypad *keypad, int r, int c);
int keypad_getKeycode(Keypad *keypad);
void keypad_buttonAction(Keypad *keypad, char key);
void keypad_update(Keypad *keypad);


#endif /* KEYPAD_H_ */