CC = gcc -g -O0

A = elf-03 elf-04
ifeq ($(filter $(A),$(notdir $(CURDIR))),)
ENTRY_FLAG =
else
ENTRY_FLAG = -Wl,-e,mystart
endif

all: elf.out static.out asm.out asm-pie.out

elf.out: elf.c
	$(CC) $< -o $@ -static -Wl,-Ttext-segment=0x10000000 $(ENTRY_FLAG)

static.out: ../static.c
	$(CC) $< -o $@ -static

asm.out: ../asm.S
	$(CC) $< -o $@ -static -nostdlib -ffreestanding

asm-pie.out: ../asm.S
	$(CC) $< -o $@ -static-pie -nostdlib -ffreestanding

clean:
	rm -f *.out

.PHONY:all clean
