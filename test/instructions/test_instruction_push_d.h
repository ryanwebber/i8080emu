#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_push_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(rom) * 3);
	rom[0] = opcode;
	rom[1] = 0;
	rom[2] = 0;

	cpu_initialize_rwm(cpu, rom, 1, 3, 0);
	cpu->d = 0x99;
	cpu->e = 0x88;
	cpu->sp = 0x03;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(cpu->d, rom[2]);
	assert_uint_eq(cpu->e, rom[1]);
	assert_uint_eq(cpu->sp, 0x01);

	free(rom);
	return 0;
}

