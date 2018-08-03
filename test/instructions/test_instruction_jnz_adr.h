#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_jnz_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, opcode, 0xFE, 0xFF
	};

	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->cc->z = 1;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(1, cpu->pc);
	
	cpu->cc->z = 0;
	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xFFFE, cpu->pc);

	return 0;
}

