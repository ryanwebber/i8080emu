#include "cpu.h"

int main() {
	BloomCPU* cpu = cpu_create();

	uint8_t data[1] = {
		0x0
	};

	if (cpu_initialize_rom(cpu, data, 8, 0)) {
		return 1;
	}

	int retval = cpu_start(cpu);
	cpu_destroy(cpu);
	return retval;
}

