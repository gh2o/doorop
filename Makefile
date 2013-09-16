PROGNAME = doorop

CFLAGS = -std=c++11 -mmcu=atmega328 -Os -Wall -Wextra -fno-use-cxa-atexit
LDFLAGS =

all: $(PROGNAME).bin

$(PROGNAME).bin: $(PROGNAME).elf
	avr-objcopy -O binary $^ $@

$(PROGNAME).elf: $(PROGNAME).cxx $(wildcard *.h)
	avr-g++ $< -o $@ $(CFLAGS) $(LDFLAGS)

flash: $(PROGNAME).bin
	avrdude -c usbasp -p atmega328 \
		-V -U flash:w:$(PROGNAME).bin

clean:
	rm -f $(PROGNAME).bin $(PROGNAME).elf

.PHONY: all flash
