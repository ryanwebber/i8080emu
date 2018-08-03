#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_ret(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[3] = {
		opcode, 0x99, 0x88
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->sp = 0x0001;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x8899, cpu->pc);
	assert_uint_eq(0x0003, cpu->sp);

	return 0;
}

