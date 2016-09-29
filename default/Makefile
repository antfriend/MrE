###############################################################################
# Makefile for the project MisterE
###############################################################################

## General Flags
PROJECT = MisterE
MCU = atmega8
TARGET = MisterE.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99           -DF_CPU=8000000UL -O1 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=MisterE.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = Main.o Motors.o Prox.o Compass.o SerialCereal.o StateOfMind.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) MisterE.hex MisterE.eep MisterE.lss size

## Compile
Main.o: ../Main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Motors.o: ../Motors.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Prox.o: ../Prox.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Compass.o: ../Compass.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

SerialCereal.o: ../SerialCereal.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

StateOfMind.o: ../StateOfMind.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) MisterE.elf dep/* MisterE.hex MisterE.eep MisterE.lss MisterE.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

