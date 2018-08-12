#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_adi(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, 0x66, opcode, 0xfe
	};

	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->a = 0x01;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x67, cpu->a);
	assert_uint_eq(0, cpu->flags->c);

	cpu->a = 0xd6;

	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xd4, cpu->a);
	assert_uint_eq(1, cpu->flags->c);

	return 0;
}

