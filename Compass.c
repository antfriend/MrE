//////////////////////////////////////*
//////////////////////////////////////////////////////////*
//               COMPASS
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
//from HM55bSample.c
//http://www.acmesystems.it/?id=114
/*

A falling edge (a transition from high to low) 
on /Enable pin will tell the chip to expect 
a command, that will be ended by a raising edge, 
again on /Enable. The commands are sent out 
serially one bit a time by raising Clock 
and then setting the required level on Dout pin. 
Same goes for reading from Din: raise Clock, 
read level, lower Clock. 

It is also possible to connect Dout and Din, 
and save one IO pin for connecting other hardware. 

To obtain a measure of the magnetic field, you 
need to send a RESET followed by a START MEASURE 
command. Then, you loop asking for status until 
the device signals that the measurement is 
complete, at which point you can get the x,y data 
from Din as two 11 bit quantities. 

*/
#include <avr/io.h>
//#include <stdlib.h>
#include <math.h>
#include <util/delay.h>
#include "Main.h"

#define COMPASS_PORT     PORTD
#define DIO_pin     PD0
#define CLK_pin     PD1
#define EN_pin     PD2

//functions
void ShiftOut(int Value, int BitsCount)
{
	for(int i=BitsCount; i>=0;i--)
	{
		bit_clear(COMPASS_PORT, CLK_pin);
		if((Value & 1 << i) == (1 << i))
		{
			bit_set(COMPASS_PORT, DIO_pin);		// 1
		}
		else
		{
			bit_clear(COMPASS_PORT, DIO_pin);	// 0
		}
		bit_set(COMPASS_PORT, CLK_pin);
		delayms(1);
	}
}

int ShiftIn(int BitsCount)
{
	int ShiftIn_Result=0;
	//set DIO_pin for input mode
	bit_clear(DDRD,DIO_pin);
	for(int i=BitsCount; i >= 0; i--)
	{
		bit_set(COMPASS_PORT, CLK_pin);
		_delay_us(1);
		if(bit_get(COMPASS_PORT,DIO_pin))
		{
			ShiftIn_Result=(ShiftIn_Result << 1)+1;
		}
		else
		{
			ShiftIn_Result=(ShiftIn_Result << 1)+0;
		}
		bit_clear(COMPASS_PORT, CLK_pin);
		_delay_us(1);
	}
	//if bit 11 is set, the value is negative
	// the representation of negative values you
	// have to add B11111000 in the upper Byte of
	// the integer.
	// see: http://en.wikipedia.org/wiki/Two%27s_complement
	if((ShiftIn_Result &1 << 11) == 1 << 11)
	{
		ShiftIn_Result=(0b11111000 << 8) | ShiftIn_Result; 
	}
	return ShiftIn_Result;
}

void HM55B_Reset()
{

//  pinMode(DIO_pin, OUTPUT);
	bit_set(DDRD,DIO_pin);
//  digitalWrite(EN_pin, LOW);
	bit_clear(COMPASS_PORT,EN_pin);
	ShiftOut(0b0000, 3);
//  digitalWrite(EN_pin, HIGH);
	bit_set(COMPASS_PORT,EN_pin);
}

void HM55B_StartMeasurementCommand() 
{
//  pinMode(DIO_pin, OUTPUT);
	bit_set(COMPASS_PORT,DIO_pin);
//  digitalWrite(EN_pin, LOW);
	bit_clear(COMPASS_PORT,EN_pin);
	ShiftOut(0b1000, 3);
//  digitalWrite(EN_pin, HIGH);
	bit_set(COMPASS_PORT,EN_pin);
}

int HM55B_ReadCommand() 
{
  int result = 0;
//  pinMode(DIO_pin, OUTPUT);
	bit_set(COMPASS_PORT,DIO_pin);
//  digitalWrite(EN_pin, LOW);
	bit_clear(COMPASS_PORT,EN_pin);

	ShiftOut(0b1100, 3);
	result = ShiftIn(3);
 	return result;
}

void setup() 
{
//  Serial.begin(115200);
//  pinMode(EN_pin, OUTPUT);
//  pinMode(CLK_pin, OUTPUT);
//  pinMode(DIO_pin, INPUT);

	HM55B_Reset();
}

void loop() 
{
/*
  HM55B_StartMeasurementCommand(); // necessary!!
  delay(40); // the data is 40ms later ready
  Serial.print(HM55B_ReadCommand()); // read data and print Status
  Serial.print(" ");  
  X_Data = ShiftIn(11); // Field strength in X
  Y_Data = ShiftIn(11); // and Y direction
  Serial.print(X_Data); // print X strength
  Serial.print(" ");
  Serial.print(Y_Data); // print Y strength
  Serial.print(" ");
  digitalWrite(EN_pin, HIGH); // ok deselect chip
  angle = 180 * (atan2(-1 * Y_Data , X_Data) / M_PI); // angle is atan( -y/x) !!!
  Serial.print(angle); // print angle
  Serial.println("");
*/
}
 





