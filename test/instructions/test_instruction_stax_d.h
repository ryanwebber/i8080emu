#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_stax_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 2);
	rom[0] = opcode;
	rom[1] = 0x00;

	cpu_initialize_rwm(cpu, rom, 0, 2, 0);
	cpu->d = 0x00;
	cpu->e = 0x01;
	cpu->a = 0x55;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, rom[1]);

	free(rom);
	return 0;
}

