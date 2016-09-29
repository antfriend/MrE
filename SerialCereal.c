#include <avr\io.h>
#include "SerialCereal.h"
//defines
#define DD_MOSI    PINB3
#define DD_SCK     PINB5
#define DDR_SPI    PORTB
//#define COMPASS_PORT     PORTD
//#define DIO_pin     PD0
//#define CLK_pin     PD1
//#define EN_pin     PD2

void SPI_MasterInit(void)
{
	// Set MOSI and SCK output, all others input
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	// Enable SPI, Master, set clock rate fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

void SPI_MasterRecieve(char cData)
{
	//
	/* Start transmission */
	//SPDR = cData;
	/* Wait for transmission complete */
	//while(!(SPSR & (1<<SPIF)));
	//
}

int SampleSerial(void) 
{
	SPI_MasterInit();
	SPI_MasterTransmit('A');  
	 
	while(1) 
	{
		// 
	}
}

