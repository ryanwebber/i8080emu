#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_push_psw(uint8_t opcode, BloomCPU *cpu) {
	uint8_t *rom = malloc(sizeof(uint8_t) * 3);
	rom[0] = opcode;
	rom[1] = 0x00;
	rom[2] = 0x00;

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->sp = 0x0003;
	cpu->a = 0x55;
	cpu->flags->z = 0x1;
	cpu->flags->s = 0x1;
	cpu->flags->p = 0x1;
	cpu->flags->c = 0x1;
	cpu->flags->a = 0x1;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, rom[2]);
	assert_uint_eq(0x1F, rom[1]);

	free(rom);
	return 0;
}

