#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_rm(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, opcode, 0x99, 0x88
	};

	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->sp = 0x0002;
	cpu->flags->s = 0;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x01, cpu->pc);

	cpu->flags->s = 1;

	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x8899, cpu->pc);
	assert_uint_eq(0x0004, cpu->sp);

	return 0;
}
