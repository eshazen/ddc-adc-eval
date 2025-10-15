#
# Makefile for AVR code
#
# NOTE: edit F_OSC and DUDPORT to support either directly programming
# the hardware using a programming cable, or Arduino bootloader.
#

# options: uno, avr
chip=avr
# options: avrisp2, usbtiny, arduino
prog=usbtiny

$(info chip is $(chip))
$(info programmer is $(prog))

# 328 for arduino and target board
ifeq ($(chip),uno)
MCU = atmega328
F_OSC = 16000000
EXTRAOPT = -Wno-discarded-qualifiers -DUNO_TARGET
DUDEMCU = m328p
endif

ifeq ($(chip),avr)
MCU = atmega328
F_OSC = 16000000
EXTRAOPT = -Wno-discarded-qualifiers -DAVR_TARGET
DUDEMCU = m328p
endif

ifeq ($(prog), usbtiny)
DUDEPORT  = -c usbtiny -P usb
endif

ifeq ($(prog), avrisp2)
DUDEPORT  = -c avrispv2 -P usb
endif

ifeq ($(prog), arduino)
DUDEPORT  = -c arduino -P /dev/ttyACM0
endif

$(info MCU is $(MCU))
$(info DUDPORT is $(DUDEPORT))
$(info EXTRAOPT is $(EXTRAOPT))
$(info F_OSC is $(F_OSC))

# CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lprintf_min -lm -DUART_GET_STRING_USED
CFLAGS = -g -Os -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -Wl,-u,vfprintf -lm -DUART_GET_STRING_USED
# no-optimization settings for interrupt code
CFLAGS_NOOPT = -g -O0 -mmcu=$(MCU) $(EXTRAOPT) -DF_CPU=$(F_OSC) -I../util -Wl,-u,vfprintf -lprintf_min

LDFLAGS = -Wl,-Map=$(<:.o=.map),--cref -mmcu=$(MCU)

# lfuse default 0x62 write as 0xe2 to disable CLKDIV8
# lfuse default 0x62 write as 0xe0 to disable CLKDIV8 and set OSC=ext
FUSEOPT = -U lfuse:w:0xe0:m

RFUSEOPT = -U hfuse:r:-:h -U lfuse:r:-:h -U efuse:r:-:h

AVRDUDE  = avrdude $(DUDEPORT) -p $(DUDEMCU) -y -u 

objects = main.o uart.o parse.o timer.o ddc.o i2c.o led.o avr_adc.o

headers = parse.h uart.h timer.h ddc.h i2c.h led.h avr_adc.h

all: $(objects)  main.hex list

clean:
	rm -f *.o *~ *.hex *.elf *.map *.lst

flash: main.hex
	$(AVRDUDE) -U flash:w:$^:i

list:
	avr-objdump -h -S main.elf > main.lst
	avr-size main.elf
	avr-size --common -x main.elf

$(objects): %.o: %.c $(headers)
	avr-gcc -c $(CFLAGS) $< -o $@

main.elf: $(objects)
	avr-gcc $(LDFLAGS) $(objects) -o $@

main.hex: main.elf
	avr-objcopy -j .text -j .data -O ihex $< $@

fuse:
	$(AVRDUDE) $(FUSEOPT)

rfuse:
	$(AVRDUDE) $(RFUSEOPT)
