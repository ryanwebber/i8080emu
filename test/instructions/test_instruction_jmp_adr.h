#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_jmp_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, 0xFF, 0xFE, 0x66
	};

	cpu_initialize_rom(cpu, rom, 1, 0);

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0xFEFF, cpu->pc);

	return 0;
}

