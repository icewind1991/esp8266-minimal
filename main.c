#include <stddef.h>
#include <stdint.h>
#include "esp8266.h"

#define PRINT 1

// Write to the internal control bus (using I2C?).
// Signature found here:
// https://github.com/espressif/esp-idf/blob/64654c04447914610586e1ac44457510a5bf7191/components/soc/esp32/i2c_rtc_clk.h#L32
void rom_i2c_writeReg(uint8_t block, uint8_t host_id, uint8_t reg_add, uint8_t data);

extern uint32_t _bss_start;
extern uint32_t _bss_end;

#if PRINT
static const char *message = "Hello world!\r\n";
static const size_t message_len = 14;
#endif

void sleep_ns(uint64_t nanoseconds);

int main(void) {
    // Clear .bss section. .data has already been loaded by the ROM bootloader.
    // This may be unnecessary for very small programs.
    uint32_t *addr;
    for (addr = &_bss_start; addr < &_bss_end; addr++) {
        *addr = 0;
    }

    // Initialize PLL.
    // I'm not quite sure what this magic incantation means, but it does set the
    // esp8266 to the right clock speed. Without this, it is running too slow.
    rom_i2c_writeReg(103, 4, 1, 136);
    rom_i2c_writeReg(103, 4, 2, 145);

    // Initialize UART.
#if PRINT
    UART0->CLKDIV = 80000000 / 115200;
#endif

    // Initialize timer. Bits:
    //  7:   timer enable
    //  6:   automatically reload when hitting 0
    //  3-2: divide by 256
    FRC1->CTRL = (1<<7) | (1<<6) | (2<<2);
    FRC1->LOAD = 0x3fffffu;  // set all 22 bits to 1
    FRC1->COUNT = 0x3fffffu; // set all 22 bits to 1

    // Set pin 2 to function GPIO2.
    // Pin 2 is mapped to pad number 13.
    IO_MUX->PIN[13] = 0 << 4; // function 0 at bit position 4

    // Set pin 2 as output.
    GPIO->ENABLE_W1TS = 1 << 2;

    while (1) {
        GPIO->OUT_W1TC = 1 << 2; // LED on
#if PRINT
        for (int i = 0; i < message_len; i++) {
            UART0->FIFO = message[i];
        }
#endif
        sleep_ns(500000000);

        GPIO->OUT_W1TS = 1 << 2; // LED off
        sleep_ns(500000000);
    }
}

// sleep_ns busy-waits until the given number of nanoseconds have passed.
void sleep_ns(uint64_t nanoseconds) {
    // 3600 = 1e9 / (80MHz / 256)
    uint32_t ticks = nanoseconds / 3600UL;
    uint32_t startTicks = FRC1->COUNT;
    // Note: COUNT counts downwards.
    while (((startTicks - FRC1->COUNT) & 0x3fffffu) < ticks) {
    }
}
