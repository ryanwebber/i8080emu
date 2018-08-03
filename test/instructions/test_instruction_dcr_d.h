#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_dcr_d(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[1] = {
		opcode
	};

	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->d = 0x99;

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x98, cpu->d);

return 0;
}

