#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_mvi_m(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(3 * sizeof(uint8_t));
	rom[0] = opcode;
	rom[1] = 0x99;
	rom[2] = 0x00;

	cpu_initialize_rwm(cpu, rom, 2, 3, 0);
	cpu->h = 0x00;
	cpu->l = 0x02;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x99, rom[2]);

	free(rom);
	return 0;
}

