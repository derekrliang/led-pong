/*
 * score.h
 *
 * Created: 6/2/2013 9:50:36 AM
 *  Authors: Orson Teodoro
 *           Derek Liang
 */ 


#ifndef SCORE_H_
#define SCORE_H_

typedef unsigned char Score;

void score_clear(Score *score);
void score_awardPoint(Score *score);
unsigned char score_getPoints(Score *score);

#endif /* SCORE_H_ */