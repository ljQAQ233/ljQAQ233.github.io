ENTRY(_start)

PHDRS
{
  pt_0 PT_LOAD FLAGS(5);
  pt_1 PT_LOAD FLAGS(4);
  pt_2 PT_LOAD FLAGS(4);
}

SECTIONS
{
  . = 0x400000;
  .text : { *(.text) } : pt_0
  . = 0x401000;
  .d1 : { *(.d1) } : pt_1
  . = 0x401800;
  .d2 : { *(.d2) } : pt_2
}

