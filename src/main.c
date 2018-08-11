#include "cpu.h"
#include "loader.h"
#include <stdio.h>

void usage(const char* prog) {
	printf("Usage: %s <rom>\n", prog);
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		usage(argv[0]);
		exit(1);
	}

	uint8_t *rom_data;
	uint32_t size = load(argv[1], &rom_data);
	if (rom_data == NULL && size != 0x4000) {
		printf("Unable to load the file: %s", argv[1]);
		exit(1);
	} else {
		printf("Loaded rom '%s' (%i bytes)\n", argv[1], size);
	}

	BloomCPU* cpu = cpu_create();

	/* writable memory starts at 0x2000 */
	if (cpu_initialize_rwm(cpu, rom_data, 0x2000, 0x4000, 0)) {
		return 1;
	}

	int retval = cpu_start(cpu);
	cpu_destroy(cpu);
	free(rom_data);

	return retval;
}

