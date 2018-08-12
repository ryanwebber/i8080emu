#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_rrc(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, opcode
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->a = 0x48;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x24, cpu->a);
	assert_uint_eq(0x00, cpu->flags->c);

	cpu->a = 0x49;
	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xa4, cpu->a);
	assert_uint_eq(0x01, cpu->flags->c);

	return 0;
}

