#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_ani(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, 0xa7
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->a = 0x33;
	cpu->flags->c = 1;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x23, cpu->a);
	assert_uint_eq(0, cpu->flags->c);

	return 0;
}

