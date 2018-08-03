#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_mov_m_a(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 2);
	rom[0] = opcode;
	rom[1] = 0x0;

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;
	cpu->a = 0x98;
	
	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x98, rom[1]);

	free(rom);
	return 0;
}

