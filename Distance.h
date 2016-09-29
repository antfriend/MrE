// Distance Measure
#ifndef Distance
#define Distance
//////////////
#include "Main.h"
#include "LEDs.h"

#define DISTANCE_CLOCK     PC5
#define DISTANCE_DATA    PC4
#define DISTANCE_PORT	PINC
#define ClockDistHigh 	bit_set(PORTC,PC5)
#define ClockDistLow 	bit_clear(PORTC,PC5)

//prototypes
void InitializeDistance(void);
int GetDistance(void);
int IsCloseEnough(int TooFar, int TooClose, int daTestValue);

//functions
void InitializeDistance(void)
{
	bit_set(DDRC,5);//set pin for output to Distance
	bit_clear(DDRC,DISTANCE_DATA);//set pin for input from Distance
	bit_set(PORTC,DISTANCE_DATA);//turn on pull-up resistor
	ClockDistHigh; //bit_set(DISTANCE_PORT,DISTANCE_IN);//D IN is normally high
}

int GetDistance(void)
{
	int daDistanceIs=0;
	int us_time=50;//optimal
	ClockDistHigh;
	delayms(4);
	ClockDistLow;
	for(int i=0;i<=30;++i)
	{
		delayms(1);
		//_delay_us(900);
		if(bit_get(DISTANCE_PORT,DISTANCE_DATA))
		{
			//measurment is complete
			break;
		}
	}
	ClockDistHigh;
	_delay_us(us_time);
	for(int i=8; i>0; i--)
	{
		ClockDistLow;
		_delay_us(us_time);
		if (bit_get(PINC,4))
		{
			bit_clear(daDistanceIs,(i-1));
		}
		else
		{
			bit_set(daDistanceIs,(i-1));
		}
		ClockDistHigh;
		_delay_us(us_time);
	}
	ClockDistHigh;
	return daDistanceIs;
}

int IsCloseEnough(int TooFar, int TooClose, int daTestValue)
{
//  ******************************
//  DISTANCE GROUPER
//	int TooFar is farther as the number gets smaller.  Lower limit of 1
//	int TooClose is closer as the number gets bigger.  Upper limit of 254
//  ******************************
	const int STATE_NOT_CLOSE_ENOUGH=0;
	const int STATE_TOO_CLOSE=1;
//	const int STATE_YES=2;//the actual value, up to 255;
	const int CLEAR_THE_VARIABLE=0;

	//int daTestValue=CLEAR_THE_VARIABLE;
	int IsCloseEnoughResult=CLEAR_THE_VARIABLE;
//	******************************
	//daTestValue=GetDistance();

	if(daTestValue > TooFar)
	{
		if(daTestValue >= TooClose)	//*** Too Close *** Too Close *** Too Close *** 
		{
			IsCloseEnoughResult=STATE_TOO_CLOSE;
		}
		else						//*** We Are In The Zone of Goodness *** We Are In The Zone of Goodness ***
		{
			IsCloseEnoughResult=daTestValue;
		}
	}
	else							//*** Noop, Not Close Enough *** Noop, Not Close Enough ***
	{
		IsCloseEnoughResult=STATE_NOT_CLOSE_ENOUGH;
	}
	return IsCloseEnoughResult;
//	******************************
}

///////////////////
///////////////////
///////////////////
#endif
