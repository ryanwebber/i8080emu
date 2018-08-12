#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_cpi(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[6] = {
		opcode, 0x6, opcode, 0x5, opcode, 0x7
	};

	cpu_initialize_rom(cpu, rom, 6, 0);
	cpu->a = 0x6;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(1, cpu->flags->z);

	result = cpu_step(cpu);
	assert_uint_eq(0, cpu->flags->z);
	assert_uint_eq(0, cpu->flags->c);
	
	result = cpu_step(cpu);
	assert_uint_eq(0, cpu->flags->z);
	assert_uint_eq(1, cpu->flags->c);
	
	return 0;
}

