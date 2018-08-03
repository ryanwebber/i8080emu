#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_ldax_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, 0x55
	};

	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->d = 0x00;
	cpu->e = 0x01;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, cpu->a);

	return 0;
}

