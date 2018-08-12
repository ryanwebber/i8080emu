#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_xchg(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[1] = {
		opcode
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->h = 0x99;
	cpu->l = 0x98;
	cpu->d = 0x97;
	cpu->e = 0x96;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x97, cpu->h);
	assert_uint_eq(0x96, cpu->l);
	assert_uint_eq(0x99, cpu->d);
	assert_uint_eq(0x98, cpu->e);

	return 0;
}

