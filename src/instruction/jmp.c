#include "jmp.h"
#include <stdio.h>

/**
 * Just increase the program counter by 1
 */
uint8_t inst_jmp(BloomCPU* cpu) {
	uint16_t *addr = (uint16_t*) (cpu->memory + cpu->pc + 1);
	printf("0x%04X JMP 0x%04X\n", cpu->pc, *addr);
	cpu->pc = *addr;
	return 0;
}

