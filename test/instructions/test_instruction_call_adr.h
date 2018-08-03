#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_call_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 5);
	rom[0] = opcode;
	rom[1] = 0xfe;
	rom[2] = 0x55;
	rom[3] = 0x00;
	rom[4] = 0x00;

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->sp = 5;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x3, cpu->sp);
	assert_uint_eq(0xFE, cpu->memory[3]);
	assert_uint_eq(0x55, cpu->memory[4]);

	free(rom);
	return 0;
}

