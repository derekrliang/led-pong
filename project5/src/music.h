/*
 * music.h
 *
 * Created: 6/2/2013 11:47:45 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#ifndef MUSIC_H_
#define MUSIC_H_

#define SPEAKER_PORT PORTB
#define SPEAKER_DDR DDRB
#define SPEAKER_PIN 0x00

#define SPK_ON SET_BIT(SPEAKER_PORT, SPEAKER_PIN)
#define SPK_OFF CLR_BIT(SPEAKER_PORT, SPEAKER_PIN)

//instrument frequencies
//http://www.contrabass.com/pages/frequency.html

// Period Definitions: (255 dynamic range)
#define B2 809
#define C3 764
#define C_SHARP_3 721
#define D3 681
#define D_SHARP_3 642
#define E3 606
#define F3 572
#define G3 510
#define A3 454
#define B3 404
#define A4 227
#define B4 202 //max including this
#define C5 191
#define C_SHARP_5 180
#define D5 170
#define D_SHARP_5 161
#define E5 152
#define F5 143
#define F_SHARP_5 135
#define G5 128
#define G_SHARP_5 120
#define A5 114
#define A_SHARP_5 107
#define B5 101
#define C6 96
#define C_SHARP_6 90
#define D6 85
#define D_SHARP_6 80
#define F6 71
#define F_SHARP_6 67
#define G6 63
#define A6 56
#define A_SHARP_6 53
#define B6 50
#define C7 47
#define D7 42
#define E7 37
#define F7 35
#define G7 31
#define A7 28
#define B7 25
#define C8 23
#define D8 21
#define REST 0

typedef struct _Note
{
	unsigned char period;
	unsigned char dur;
} Note;

enum NoteLengths
{
	WHOLE = 20,
	HALF = WHOLE / 2,
	HALFDOT = HALF + HALF / 2,
	QUARTER = HALF / 2,
	QUARTERDOT = QUARTER + QUARTER / 2,
	EIGHTH = QUARTER / 2,
	SIXTEENTH = EIGHTH / 2
};

typedef struct _Music
{
	unsigned char enable;
	unsigned char pwm; // 5% to 95%
	unsigned char tempo;
	unsigned char _fastForward;
	int octave_offset;
} Music;

void music_fastFoward(Music *music);
void music_volumeIncrease(Music *music);
void music_volumeDecrease(Music *music);
void music_tempoDown(Music *music);
void music_tempoUp(Music *music);
void music_octaveUp(Music *music);
void music_octaveDown(Music *music);
void music_toggle(Music *music);
void music_playNote(Music *music, Note n);
void music_playSong(Music *music, Note* song, unsigned char size);
unsigned int music_translatePeriod(Music *music, unsigned int period);
void music_init(Music *music);
void music_playGreenSleeves(Music *music);
void music_playSoundEffectBeep(Music *music);
void music_wait(long msec);
void music_disable(Music *music);
void music_enable(Music *music);
void music_wait2(long msec);

void music_playNyanCat(Music *music);

#endif /* MUSIC_H_ */