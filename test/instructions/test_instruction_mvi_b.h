#include <stdint.h>
#include "../assertions.h"
#include "../../src/cpu.h"

extern uint8_t test_instruction_mvi_b(uint8_t opcode, BloomCPU *cpu) {
	uint8_t rom[2] = {
		opcode, 0x55
	};

	cpu_initialize_rom(cpu, rom, 2, 0);

	uint8_t result = cpu_step(cpu);
	assert_uint_eq(0, result);
	assert_uint_eq(0x55, cpu->b);

return 0;
}
