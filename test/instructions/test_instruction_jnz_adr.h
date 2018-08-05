#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_jnz_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[6] = {
		opcode, 0x00, 0x00, opcode, 0xFE, 0xFF
	};

	cpu_initialize_rom(cpu, rom, 6, 0);
	cpu->flags->z = 1;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(3, cpu->pc);
	
	cpu->flags->z = 0;
	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xFFFE, cpu->pc);

	return 0;
}

