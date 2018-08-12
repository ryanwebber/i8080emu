#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_dad_h(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, opcode
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x01;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x02, cpu->h);
	assert_uint_eq(0x02, cpu->l);
	assert_uint_eq(0x00, cpu->flags->c);

	cpu->h = 0xF0;
	cpu->l = 0xF0;
	
	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xE1, cpu->h);
	assert_uint_eq(0xE0, cpu->l);
	assert_uint_eq(0x01, cpu->flags->c);
	
	return 0;
}

