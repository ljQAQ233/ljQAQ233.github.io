ENTRY(_start)

SECTIONS
{
  . = 0x400000;
  .text : { *(.text) }
  . = 0x401000;
  .d1 : { *(.d1) } : pt_1
  . = 0x401800;
  .d2 : { *(.d2) } : pt_2
}
