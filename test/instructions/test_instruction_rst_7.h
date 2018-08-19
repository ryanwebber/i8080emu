#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_rst_7(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 3);
	rom[0] = opcode;
	rom[1] = 0x00;
	rom[2] = 0x00;

	cpu_initialize_rwm(cpu, rom, 1, 3, 0);
	cpu->sp = 0x0003;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x38, cpu->pc);
	assert_uint_eq(0x01, cpu->sp);
	assert_uint_eq(0x03, rom[1]);
	assert_uint_eq(0x00, rom[2]);

	return 0;
}

