/* Linker script for the ESP8266 */

MEMORY
{
    /* Data RAM. Allows byte access. */
    DRAM  (rw) : ORIGIN = 0x3FFE8000, LENGTH = 80K
    /* Instruction RAM. */
    IRAM  (x)  : ORIGIN = 0x40100000, LENGTH = 32K
}

/* The entry point. It is set in the image flashed to the chip, so must be
 * defined.
 */
ENTRY(main)


/* Define output sections */
SECTIONS {
  .dram0.data :
  {
    _data_start = ABSOLUTE(.);
    *(.data)
    *(.data.*)
    _data_end = ABSOLUTE(.);
  } >DRAM
  /* Shared RAM */
  .dram0.bss (NOLOAD) :
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);
    *(.bss)
    *(.bss.*)
    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
  } >DRAM

  _sidata = LOADADDR(.dram0.data);

  .dram0.rodata :
  {
    _rodata_start = ABSOLUTE(.);
    *(.rodata)
    *(.rodata.*)
    _rodata_end = ABSOLUTE(.);
    . = ALIGN(4);
    _heap_start = ABSOLUTE(.);
  } >DRAM

  .iram.text :
  {
    _stext = .;
    _text_start = ABSOLUTE(.);
    *(.literal .text .literal.* .text.*)
    _text_end = ABSOLUTE(.);
    _etext = .;
  } > IRAM

    /* Constant literals and code. Loaded into IRAM for now. Eventually, most
     * code should be executed directly from flash.
     * Note that literals must be before code for the l32r instruction to work.
     */
    .text : ALIGN(4)
    {
        *(.literal .text)
        *(.literal.* .text.*)
    } >IRAM
}

/* Compiler runtime functions provided by the ROM.
 */
__adddf3      = 0x4000c538;
__addsf3      = 0x4000c180;
__divdf3      = 0x4000cb94;
__divdi3      = 0x4000ce60;
__divsi3      = 0x4000dc88;
__extendsfdf2 = 0x4000cdfc;
__fixdfsi     = 0x4000ccb8;
__fixunsdfsi  = 0x4000cd00;
__fixunssfsi  = 0x4000c4c4;
__floatsidf   = 0x4000e2f0;
__floatsisf   = 0x4000e2ac;
__floatunsidf = 0x4000e2e8;
__floatunsisf = 0x4000e2a4;
__muldf3      = 0x4000c8f0;
__muldi3      = 0x40000650;
__mulsf3      = 0x4000c3dc;
__subdf3      = 0x4000c688;
__subsf3      = 0x4000c268;
__truncdfsf2  = 0x4000cd5c;
__udivdi3     = 0x4000d310;
__udivsi3     = 0x4000e21c;
__umoddi3     = 0x4000d770;
__umodsi3     = 0x4000e268;
__umulsidi3   = 0x4000dcf0;

/* Proprietary ROM function needed for proper clock configuration.
 */
rom_i2c_writeReg = 0x400072d8;
