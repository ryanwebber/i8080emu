#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_lxi_b(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[3] = {
		opcode, 0xFF, 0xFE
	};

	cpu_initialize_rom(cpu, rom, 3, 0);

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xFE, cpu->b);
	assert_uint_eq(0xFF, cpu->c);

	return 0;
}

