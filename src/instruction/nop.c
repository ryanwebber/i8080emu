#include "nop.h"
#include <stdio.h>

/**
 * Just increase the program counter by 1
 */
uint8_t inst_nop(BloomCPU* cpu) {
	printf("0x%04X NOP\n", cpu->pc * 8);
	cpu->pc += 1;
	return 0;
}

