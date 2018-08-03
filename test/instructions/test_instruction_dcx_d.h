#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_dcx_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[1] = {
		opcode
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->d = 0x32;
	cpu->e = 0x10;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x32, cpu->d);
	assert_uint_eq(0x0f, cpu->e);

	return 0;
}

