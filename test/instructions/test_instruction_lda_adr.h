#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_lda_adr(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[4] = {
		opcode, 0x03, 0x00, 0x67
	};

	cpu_initialize_rom(cpu, rom, 1, 0);

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x67, cpu->a);

	return 0;
}

