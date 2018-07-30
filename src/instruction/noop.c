#include "noop.h"

/**
 * Just increase the program counter by 1
 */
uint8_t inst_noop(BloomCPU* cpu) {
	cpu->pc += 1;
	return 0;
}

