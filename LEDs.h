//////////////////////////////////////*
//////////////////////////////////////////////////////////*
#ifndef LEDs //               LEDs
#define LEDs
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
#include "Main.h"

#define LEDs_PORT   PORTB
#define RED_LED     PB3
#define BLUE_LED    PB4
#define GREEN_LED   PB5
#define R_On 		bit_set(LEDs_PORT,RED_LED);
#define R_Off 		bit_clear(LEDs_PORT,RED_LED);
#define G_On 		bit_set(LEDs_PORT,GREEN_LED);
#define G_Off 		bit_clear(LEDs_PORT,GREEN_LED);
#define B_On 		bit_set(LEDs_PORT,BLUE_LED);
#define B_Off 		bit_clear(LEDs_PORT,BLUE_LED);
#define ALL_Off		R_Off;G_Off;B_Off;

//prototypes
void InitLEDs(void);
void ShowLEDvalue(int GitValue);
void BlinkANumber(int BitsCount, int GitValue);
void BlinkAll(void);

//functions
void InitLEDs(void)
{
	//set pins for output
	bit_set(DDRB,RED_LED);
	bit_set(DDRB,GREEN_LED);
	bit_set(DDRB,BLUE_LED);
}

void ShowLEDvalue(int GitValue)
{
	ALL_Off;
	switch(GitValue)
	{
		case 3 : //
			R_On;
			break;
		case 2 : //
			G_On;
			break;
		case 1 : //
			B_On;
			break;
	}
	if (GitValue >= 4)
	{
		R_On;
		G_On;
		B_On;
	}
}

void BlinkANumber(int BitsCount, int GitValue)
{
	int BlinkDelay=250;
	ALL_Off;
//	G_On;
	delayms(BlinkDelay);
	ALL_Off;
//	R_On;
//	G_On;
//	B_On;
//	delayms(BlinkDelay);
	
	//blink out a binary representation of a number, MSB first
	//BitsCount--;
	for(int i=BitsCount-1; i>=0; i--)
	{
		ALL_Off;
//		G_On;
		delayms(BlinkDelay/2);ALL_Off;//Green is the pause color
		if (bit_get(GitValue,i))//return ~daPORT & (1<<daBIT)
		{
			//Red is a ZERO
			R_On;
		}
		else
		{
			//Blue is a ONE
			B_On;
		}
		delayms(BlinkDelay);
	}
	ALL_Off;
	delayms(3*BlinkDelay);
}

void BlinkAll(void)
{
	R_On;G_On;B_On;delayms(500);
	ALL_Off;delayms(500);
}

///////////////////////////////////////////////////////
//////////////////////////////////////
////////////////////////
///////////////////
#endif


