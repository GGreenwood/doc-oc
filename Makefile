PROJECTNAME = doc-oc
DEVICE = atmega328p
PORT = /dev/ttyUSB0
BAUDRATE = 57600
PROGRAMMER = arduino
F_CPU = 16000000
CC = avr-gcc
AVROBJCOPY = avr-objcopy

CFLAGS = -Wall -Os -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) -std=gnu99
OBJFLAGS = -j .text -j .data -O ihex
AVRFLAGS = -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(BAUDRATE)

COBJECTS = $(patsubst %.c, %.o, $(shell find $(SOURCEDIR) -name '*.c'))
ASMOBJECTS = $(patsubst %.S, %.o, $(shell find $(SOURCEDIR) -name '*.S'))
OBJECTS = $(COBJECTS) $(ASMOBJECTS)
HEADERS = $(wildcard *.h)

TARGET = $(PROJECTNAME).hex

all:	$(TARGET)

flash:	$(TARGET)
	avrdude $(AVRFLAGS) -U flash:w:$(TARGET)

clean:
	rm -f *.0 *.hex *.o *.elf

fuse:
	avrdude $(AVRFLAGS) -U efuse:w:$(EFUSE):m -U hfuse:w:$(HFUSE):m -U lfuse:w:$(LFUSE):m

%.hex: %.elf
	$(AVROBJCOPY) $(OBJFLAGS) $< $@

$(PROJECTNAME).elf: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# From C source to .o object file
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# From assembler source to .o object file
%.o: %.S $(HEADERS)
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

