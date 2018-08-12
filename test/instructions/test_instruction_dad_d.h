#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_dad_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, opcode
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x01;
	cpu->l = 0x01;
	cpu->d = 0x02;
	cpu->e = 0x03;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x03, cpu->h);
	assert_uint_eq(0x04, cpu->l);
	assert_uint_eq(0x00, cpu->flags->c);

	cpu->h = 0xF0;
	cpu->l = 0xF0;
	cpu->d = 0xF1;
	cpu->e = 0xF2;

	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xE2, cpu->h);
	assert_uint_eq(0xE2, cpu->l);
	assert_uint_eq(0x01, cpu->flags->c);
	
	return 0;
}

