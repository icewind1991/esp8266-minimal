all: build/firmware.elf

CC      = xtensa-lx106-elf-gcc
CFLAGS  = -Os -g -Wall -Werror -nostdlib -mlongcalls -std=c11
LDFLAGS = -Wl,--gc-sections -T esp8266.ld

flash: build/firmware.elf
	esptool.py elf2image build/firmware.elf
	esptool.py --port /dev/ttyUSB0 write_flash 0x00000 build/firmware.elf-0x00000.bin -ff 80m -fm dout

clean:
	rm -rf build

build/firmware.elf: main.c esp8266.h
	@mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ main.c
	size $@
