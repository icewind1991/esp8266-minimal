// Most of the register information in here comes from the appendix in this
// document:
// https://www.espressif.com/sites/default/files/documentation/esp8266-technical_reference_en.pdf
// Some more information comes from the *_register.h files here:
// https://github.com/esp8266/Arduino/tree/master/tools/sdk/include

#pragma once

#include <stdint.h>

typedef struct {
    volatile uint32_t FIFO;
    volatile uint32_t INT_RAW;
    volatile uint32_t INT_ST;
    volatile uint32_t INT_ENA;
    volatile uint32_t INT_CLR;
    volatile uint32_t CLKDIV;
    volatile uint32_t AUTOBAUD;
    volatile uint32_t STATUS;
    volatile uint32_t CONF0;
    volatile uint32_t CONF1;
    volatile uint32_t LOWPULSE;
    volatile uint32_t HIGHPULSE;
    volatile uint32_t RXD_CNT;
    volatile uint32_t DATE;
    volatile uint32_t ID;
} UART_Type;

typedef struct {
    volatile uint32_t OUT;
    volatile uint32_t OUT_W1TS;
    volatile uint32_t OUT_W1TC;
    volatile uint32_t ENABLE;
    volatile uint32_t ENABLE_W1TS;
    volatile uint32_t ENABLE_W1TC;
    volatile uint32_t IN;
    volatile uint32_t STATUS;
    volatile uint32_t STATUS_W1TS;
    volatile uint32_t STATUS_W1TC;
    volatile uint32_t PIN[16];
    volatile uint32_t SIGMA_DELTA;
    volatile uint32_t RTC_CALIB_SYNC;
    volatile uint32_t RTC_CALIB_VALUE;
} GPIO_Type;

typedef struct {
    volatile uint32_t LOAD;
    volatile uint32_t COUNT;
    volatile uint32_t CTRL;
    volatile uint32_t INT;
    volatile uint32_t ALARM; // only available in FRC2
} FRC_Type;

typedef struct {
    volatile uint32_t CONF;
    // The pins appear to have the following bits defined:
    //   bit 0:   output enable
    //   bit 1:   sleep output enable
    //   bit 2:   sleep pullup 2
    //   bit 3:   sleep pullup
    //   bit 4-5: lower bits of the pin function
    //   bit 6:   pullup 2
    //   bit 7:   pullup
    //   bit 8:   upper bit of the pin function
    // Source:
    // https://github.com/esp8266/Arduino/blob/11ae243ecf00bd80c1d5aacde95ca20e92e2cb74/tools/sdk/include/eagle_soc.h#L217-L224
    volatile uint32_t PIN[17];
} IO_MUX_Type;

#define UART0  ((UART_Type*)(0x60000000))
#define GPIO   ((GPIO_Type*)(0x60000300))
#define FRC1   ((FRC_Type*)(0x60000600)) // timer 1
#define FRC2   ((FRC_Type*)(0x60000620)) // timer 2
#define IO_MUX ((IO_MUX_Type*)(0x60000800))
