#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_pop_psw(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[3] = {
		opcode, 0x1f, 0x55
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->sp = 0x0001;
	
	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, cpu->a);
	assert_uint_eq(0x01, cpu->flags->z);
	assert_uint_eq(0x01, cpu->flags->s);
	assert_uint_eq(0x01, cpu->flags->p);
	assert_uint_eq(0x01, cpu->flags->c);
	assert_uint_eq(0x01, cpu->flags->a);

	return 0;
}

