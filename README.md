# Bare minimum ESP8266

This is a very minimal ESP8266 program, inspired by
[nosdk8266](https://github.com/cnlohr/nosdk8266). It is pure C with no SDK parts
left apart from one function declaration.

Code size on my version of the ESP8266 toolchain (GCC 4.8.5):

| configuration    | text      | data | bss |
| ---------------- | --------- | ---- | --- |
| UART enabled     | 302 bytes | 0    | 0   |
| UART disabled    | 243 bytes | 0    | 0   |
| only timer + LED | 179 bytes | 0    | 0   |

You could trim this down even further with a delay loop instead of using a
timer.

## How to use

Simply run:

    make flash

I recommend [picocom](https://github.com/npat-efault/picocom) to see the serial
output:

    picocom --baud 115200 /dev/ttyUSB0

## Why?

To understand how the ESP8266 works, outside of the SDK. I learned this while
[porting TinyGo to the ESP8266](https://github.com/tinygo-org/tinygo/pull/900)
and decided to share what I have learned. It may be useful to other people who
would like to avoid the SDK, for reasons such as code size, compilation speed,
or porting a new language.

## License

Licensed under the BSD 2-clause license, see the LICENSE file for details.
Feel free to use portions however you want (attribution appreciated but not
required). However, note that some parts (such as the register definitions)
might still be copyrighted by Espressif.
