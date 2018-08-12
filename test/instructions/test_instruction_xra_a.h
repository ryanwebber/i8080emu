#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_xra_a(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[1] = {
		opcode
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->a = 0x11;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0, cpu->a);
	assert_uint_eq(1, cpu->flags->z);
	assert_uint_eq(0, cpu->flags->s);
	assert_uint_eq(1, cpu->flags->p);
	assert_uint_eq(0, cpu->flags->c);
	assert_uint_eq(0, cpu->flags->a);

	return 0;
}

