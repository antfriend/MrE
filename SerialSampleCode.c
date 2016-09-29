#include <util/delay.h> 
#include <avr/interrupt.h> 
#define NOP asm("nop"); 
#define SPIEE_CS 4 
#define SPIEE_CS_PORT PORTB 
#define SPI_EEPROM_WREN 0x6 
#define SPI_EEPROM_RDSR 0x5 
#define SPI_EEPROM_WRITE 0x2 
#define SPI_EEPROM_READ 0x3 
uint8_t spieeprom_read (uint16_t); 
uint8_t spi_transfer (uint8_t); 
uint8_t spieeprom_write (uint16_t, uint8_t); 

int 
main (void) 
{ 
  DDRD = 0xFF;                  //  all  output on PORT D 
  DDRB = 0xDF;                  // input on MOSI/DI (for SPI), all others output 

  // deselect EEPROM 
  PORTB |= (1 << SPIEE_CS); 

  // Load data to the eeprom.  We will load one byte to memory position 100. 
  // we will load the number 51 to the eeprom 
  spieeprom_write (100, 51); 
  _delay_loop_2 (5000); 

  // Read the data back from the eeprom.  Read one byte from memory position 100 
  uint8_t buff = spieeprom_read (100); 

  // Light up some leds 
  PORTD = buff; 

  while (1) 
    { 
    } 
} 

uint8_t 
spieeprom_read (uint16_t addr) 
{ 
  // pull CS low to activate eeprom 
  SPIEE_CS_PORT &= ~(1 << SPIEE_CS); 
  NOP; 
  NOP; 
  NOP; 
  NOP;                          // wait 500 ns, CS setup time 
  // send READ command  0000 0011 
  spi_transfer (SPI_EEPROM_READ); 

  // Send in the memory address we will start to read from 
  // This is a 16 bit address.  We must send in 8 bits at a time 
  spi_transfer (addr >> 8);     // send high bits of address 
  spi_transfer (addr & 0xFF);   // send low bits of address 

  // We will read back one byte 
  uint8_t buff = spi_transfer (0); 

  // Once done with the read, set the CS high to terminate the operation 
  SPIEE_CS_PORT |= (1 << SPIEE_CS); 
  return buff; 
} 

uint8_t 
spieeprom_write (uint16_t addr, uint8_t data) 
{ 
  uint8_t i; 

  // Before performing the write, first check to see if eeprom is in the middle of 
  // a read.  Send in the Read Status (RDSR 0000 0101).  Check the returned status 
  // to see if it is ok to do a write. 
  do 
    { 
      asm ("wdr"); 
      // Activate eeprom by pulling CS low 
      SPIEE_CS_PORT &= ~(1 << SPIEE_CS); 
      NOP; 
      NOP; 
      NOP; 
      NOP;                      // wait 500 ns, CS setup time 
      spi_transfer (SPI_EEPROM_RDSR);   // write "READ STATUS REG" cmd 
      i = spi_transfer (0);     // read status 

      SPIEE_CS_PORT |= (1 << SPIEE_CS); // pull CS high 

    } 
  while ((i & 0x1) != 0); 

  // pull CS low to activate eeprom 
  SPIEE_CS_PORT &= ~(1 << SPIEE_CS); 
  NOP; 
  NOP; 
  NOP; 
  NOP;                          // wait 500 ns, CS setup time 

  // Set the write enable latch by issuing the WREN command 0000 0110 
  // then bring CS back high 
  spi_transfer (SPI_EEPROM_WREN);       // send command 
  SPIEE_CS_PORT |= (1 << SPIEE_CS);     // pull CS high 
  NOP; 
  NOP; 
  NOP; 
  NOP;                          // wait 500 ns, CS setup time 

  // Once the latch is set, proceed by setting CS low and 
  // sending the WRITE command 0000 0010 
  SPIEE_CS_PORT &= ~(1 << SPIEE_CS);    // pull CS low 
  spi_transfer (SPI_EEPROM_WRITE);      // send WRITE command 

  // Send in the memory address you will write to. 
  // The address is 16bits, so send in 8 bites at a time 
  spi_transfer (addr >> 8);     // send high bits of address 
  spi_transfer (addr & 0xFF);   // send low bits of address 

  spi_transfer (data);          // send data 
  NOP; 
  NOP; 
  NOP; 
  NOP;                          // wait 500 ns, CS setup time 
  // pull CS high to terminate operation 
  SPIEE_CS_PORT |= (1 << SPIEE_CS); 

  return 0; 
} 


// Transfer the data to the eeprom using SPI 
uint8_t spi_transfer (uint8_t c) 
{ 
	/*
  USIDR = c; 
  USISR = (1 << USIOIF); 
  while (!(USISR & (1 << USIOIF))) 
    { 
      USICR = (1 << USIWM0) | (1 << USICS1) | (1 << USICLK) | (1 << USITC); 
    } 
  return USIDR; 
  */
  return 0;
} 
