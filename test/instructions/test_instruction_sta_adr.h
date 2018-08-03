#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_sta_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 4);
	rom[0] = opcode;
	rom[1] = 0x03;
	rom[2] = 0x00;
	rom[3] = 0x00;

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->a = 0x56;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x56, cpu->memory[3]);

	free(rom);
	return 0;
}

