/*
 * music.c
 *
 * Created: 6/2/2013 11:47:55 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 

#include <asf.h>
#include "music.h"
#include "avr.h"

void music_fastFoward(Music *music)
{
	music->_fastForward = 1;
};

void music_disable(Music *music)
{
	music->enable = 0;
}

void music_enable(Music *music)
{
	music->enable = 1;
}

void music_wait(long msec) //for the Music class
{
	TCCR0 = 3; //CLKio/64 = 125000Hz //0.008ms per tick
	//0.008ms per tick
	//125000 ticks 1 second
	while (msec--) {
		TCNT0 = (unsigned char)(256 - (XTAL_FRQ / 64) * 0.00001); //1 tick left //0.008ms per loop
		SET_BIT(TIFR, TOV0); //enable overflow
		//WDR(); //reset watchdog
		while (!GET_BIT(TIFR, TOV0)); //wait till overflow
	}
	TCCR0 = 0; //stop timer
}

static inline void
sleep_700ns(void)
{
	NOP();
	NOP();
	NOP();
}

// ~7usec, ~.7usec x 10
void music_wait2(long msec)
{
	while (msec--) {
		for (unsigned char i = 0; i < 10; i++) // lower number condition => higher sounds, 10 is good
		{
			sleep_700ns();
		}
	}
}			

void music_volumeIncrease(Music *music)
{
	music->pwm < 95 ? music->pwm++ : 95;
}

void music_volumeDecrease(Music *music)
{
	music->pwm > 5 ? music->pwm-- : 5;
}

void music_tempoDown(Music *music)
{
	music->tempo > 2 ? music->tempo -= 2 : 1;
}

void music_tempoUp(Music *music)
{
	music->tempo < 253 ? music->tempo += 2 : 255;
}

void music_octaveUp(Music *music)
{
	music->octave_offset < 255 ? music->octave_offset+=1 : 127;
	//clr_lcd();
	//puts_lcd(PSTR("ADJUSTING PERIOD +"));
}

void music_octaveDown(Music *music)
{
	music->octave_offset > -255 ? music->octave_offset-=1 : -127;
	//clr_lcd();
	//puts_lcd(PSTR("ADJUSTING PERIOD -"));
}

void music_toggle(Music *music)
{
	music->enable = !music->enable;
}

void music_playNote(Music *music, Note n)
{
	unsigned int period = n.period;
	
	if (music->octave_offset != 0)
		period = music_translatePeriod(music, n.period);
	
	unsigned int tH = (music->pwm * period) / 100;
	unsigned int tL = period - tH;
	unsigned int count = (100000 * n.dur / period) / music->tempo;
	
	music->_fastForward = 0;
	for (unsigned int i = 0; i < count && !music->_fastForward; i++)
	{
		if (n.period == REST)
			SPK_OFF;
		else
			music->enable ? SPK_ON : 0;
		music_wait2(tH);
		SPK_OFF;
		music_wait2(tL);
	}
}

void music_playSong(Music *music, Note* song, unsigned char size)
{
	for (int i = 0; i < size; i++)
	{
		music_playNote(music, song[i]);
	}
}

unsigned int music_translatePeriod(Music *music, unsigned int period)
{
	return period * (music->octave_offset);
}

void music_init(Music *music)
{
	music->enable = 1;
	music->pwm = 50;
	music->octave_offset = 0;
	music->tempo = 20;
	
	// SPEAKER TO OUTPUT
	SET_BIT(SPEAKER_DDR, SPEAKER_PIN);	
}

void music_playGreenSleeves(Music *music)
{
	music->tempo = 20;

	Note greenSleeves[38] =
	{
		// FIRST SECTION (20)
		{ E5, QUARTER },
		// - 1
		{ G5, HALF },
		{ A5, QUARTER },
		{ B5, QUARTERDOT },
		{ C6, EIGHTH },
		{ B5, QUARTER },
		{ A5, HALF },
		{ F5, QUARTER },
		{ D5, QUARTERDOT },
		{ E5, EIGHTH },
		{ F5, QUARTER },
		{ G5, HALF },
		// - 2
		{ E5, QUARTER },
		{ E5, QUARTERDOT },
		{ D_SHARP_5, EIGHTH },
		{ E5, QUARTER },
		{ F5, HALF },
		{ D_SHARP_5, QUARTER },
		{ B4, HALF },
		{ E5, QUARTER },
		
		// SECOND SECTION (18)
		{ G5, HALF },
		{ A5, QUARTER },
		{ B5, QUARTERDOT },
		{ C6, EIGHTH },
		{ B5, QUARTER },
		{ A5, HALF },
		{ F5, QUARTER },
		{ D5, QUARTERDOT },
		{ E5, EIGHTH },
		{ F5, QUARTER },
		{ G5, QUARTERDOT },
		{ F5, EIGHTH },
		{ E5, QUARTER },
		{ D_SHARP_5, QUARTERDOT },
		{ C_SHARP_5, EIGHTH },
		{ D_SHARP_5, QUARTER },
		{ E5, HALFDOT + HALF }, // TIED
		
		// THIRD SECTION
	}; //20+18=38 total notes

	music_playSong(music, greenSleeves, 38);
}


void music_playSoundEffectBeep(Music *music)
{
	Note sfx[1] =
	{
		{ E5, SIXTEENTH },
	};

	music_playSong(music, sfx, 1);
}

void music_playNyanCat(Music *music)
{
	music->tempo = 20;

	Note nyanCat[69] =
	{
		/* BAR 1 */
		{ D_SHARP_5, SIXTEENTH },
		{ E5, SIXTEENTH },
		{ F_SHARP_5, EIGHTH },
		{ B6, EIGHTH },
		{ D_SHARP_5, SIXTEENTH },
		{ E5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ B6, SIXTEENTH },
		{ C_SHARP_6, SIXTEENTH },
		{ D_SHARP_6, SIXTEENTH },
		{ C_SHARP_6, SIXTEENTH },
		{ A_SHARP_6, SIXTEENTH },
		{ B6, EIGHTH },
		/* BAR 2 */
		{ F_SHARP_5, EIGHTH },
		{ D_SHARP_5, SIXTEENTH },
		{ E5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ B6, EIGHTH },
		{ C_SHARP_6, SIXTEENTH },
		{ A_SHARP_6, SIXTEENTH },
		{ B6, EIGHTH },
		{ C_SHARP_6, SIXTEENTH },
		{ E5, SIXTEENTH },
		{ D_SHARP_6, SIXTEENTH },
		{ E5, SIXTEENTH },
		{ C_SHARP_6, SIXTEENTH },
		/* BAR 3 */
		{ F_SHARP_5, SIXTEENTH },
		{ G5, SIXTEENTH },
		{ D5, EIGHTH },
		{ D5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ A_SHARP_6, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		/* BAR 4 */
		{ D_SHARP_5, EIGHTH },
		{ F_SHARP_5, EIGHTH },
		{ A_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		{ D5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ D5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D5, EIGHTH },
		{ B5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ F_SHARP_5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ D_SHARP_5, SIXTEENTH },
		{ C_SHARP_5, SIXTEENTH },
		{ B5, SIXTEENTH },
		{ C_SHARP_5, EIGHTH },
		{ B5, EIGHTH },
		{ C_SHARP_5, EIGHTH }
		};		
	
	music_playSong(music, nyanCat, 69);	
}