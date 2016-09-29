//////////////////////////////////////*
//////////////////////////////////////////////////////////*
#ifndef Jumpers //               Jumpers
#define Jumpers
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
#include "Main.h"

//#define JUMPERYS_PORT     PORTB
#define JUMPERYS_PORT     PINB
#define JUMPERY_ONE     PB1
#define JUMPERY_TWO     PB2

//prototypes
void InitJumpers(void);
int GetJumperValue(void);

//functions
void InitJumpers(void)
{
	//set pins for input
	//bit_clear(DDRB,PB1);
	//bit_clear(DDRB,PB2);
	DDRB &=~_BV(2);//Set as input
	PORTB |=_BV(2);//Enable pull up
	DDRB &=~_BV(1);//Set as input
	PORTB |=_BV(1);//Enable pull up
}

int GetJumperValue(void)
{
	int MuhGetJumpersValue=0;
	if(bit_get(JUMPERYS_PORT,JUMPERY_ONE))
	{
		if(bit_get(JUMPERYS_PORT,JUMPERY_TWO))
		{
			//both on, binary11 both jumpers on
			MuhGetJumpersValue=3;
		}
		else
		{
			//binary 10
			MuhGetJumpersValue=2;
		}
	}
	else
	{
		if(bit_get(JUMPERYS_PORT,JUMPERY_TWO))
		{
			//binary 01 
			MuhGetJumpersValue=1;
		}
		else
		{
			//binary 00, both jumpers off
			MuhGetJumpersValue=4;
		}
	}
	return MuhGetJumpersValue;
}


///////////////////////////////////////////////////////
//////////////////////////////////////
////////////////////////
///////////////////
#endif


