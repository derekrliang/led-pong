/*
 * score.c
 *
 * Created: 6/2/2013 9:50:27 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#include "score.h"

void score_clear(Score *score)
{
	*score = 0;
}

void score_awardPoint(Score *score)
{
	(*score)++;
}

unsigned char score_getPoints(Score *score)
{
	return *score;
}
