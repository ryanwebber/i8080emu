#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_inx_h(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[1] = {
		opcode
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->h = 0x55;
	cpu->l = 0x66;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, cpu->h);
	assert_uint_eq(0x67, cpu->l);

	return 0;
}

