//////////////////////////////////////*
//////////////////////////////////////////////////////////*
//               PROXIMITY DOTS
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
#include <avr/io.h>
#include "Main.h"
#include "Prox.h"

//functions
int RightProxOn(void)
{
	return bit_get(PIND,6);
	/*
	int daProxOn;
	daProxOn=~PIND & (1<<6);
	return daProxOn;
	*/
}

int LeftProxOn(void)
{
	return bit_get(PIND,5);
	/*
	int daProxOn;
	daProxOn=~PIND & (1<<5);
	return daProxOn;
	*/
}
