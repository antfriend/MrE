//////////////////////////////////////*
//////////////////////////////////////////////////////////*
#ifndef MyEepromDream //               MyEepromDream
#define MyEepromDream
/////////////////////////////////////////////////////*
//////////////////////////////////////*
////////////////////////////*
///////////////////*
#include "Main.h"
#include <avr/eeprom.h>

uint8_t ReadByteFromEeprom(void);
void WriteByteToEeprom(uint8_t x);

//variables
uint8_t EEMEM EEVar;
uint8_t ByteOfData;
volatile u16 aByteFromEeprom = 1;

//read byte function
uint8_t ReadByteFromEeprom(void)
{ 
   uint8_t temp; 
   temp = eeprom_read_byte(&EEVar);
   return(temp); 
}

// read byte usage
//ByteOfData = ReadByteFromEeprom ();

//write byte function
void WriteByteToEeprom(uint8_t x)
{ 
   eeprom_write_byte (&EEVar, x); 
}
// write byte usage
//WriteByteToEeprom (ByteOfData);




///////////////////////////////////////////////////////
//////////////////////////////////////
////////////////////////
///////////////////
#endif
