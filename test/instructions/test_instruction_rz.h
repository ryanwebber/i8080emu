#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_rz(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, opcode, 0x55, 0x44
	};

	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->flags->z = 0;
	cpu->sp = 0x02;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x0001, cpu->pc);
	assert_uint_eq(0x0002, cpu->sp);

	cpu->flags->z = 1;

	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x4455, cpu->pc);
	assert_uint_eq(0x0004, cpu->sp);

	return 0;
}
