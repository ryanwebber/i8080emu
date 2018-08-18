#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_dcr_m(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 4);
	rom[0] = opcode;
	rom[1] = opcode;
	rom[2] = 0x05;
	rom[3] = 0x01;

	cpu_initialize_rwm(cpu, rom, 2, 4, 0);
	cpu->h = 0x00;
	cpu->l = 0x02;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x04, rom[2]);
	assert_uint_eq(cpu->flags->c, 0);

	cpu->l = 0x03;

	result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x00, rom[3]);
	assert_uint_eq(cpu->flags->z, 1);

	free(rom);
	return 0;
}

