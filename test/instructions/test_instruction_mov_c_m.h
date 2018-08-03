#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_mov_c_m(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, 0x77
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x77, cpu->c);

	return 0;
}

