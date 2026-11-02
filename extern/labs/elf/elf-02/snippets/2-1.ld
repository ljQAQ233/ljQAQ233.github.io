ENTRY(_start)

SECTIONS
{
  . = 0x400000;
  .text : { *(.text) }
  . = 0x401000;
  .data : {
    *(.d1)
    . = 0x401800;
    *(.d2)
  }
}

