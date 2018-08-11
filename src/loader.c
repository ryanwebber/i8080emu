#include "loader.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t load(const char* filename, uint8_t **data_ptr) {

	FILE *f = fopen(filename, "rb");
	
	if (f == NULL) {
		*data_ptr = 0;
		return 0;
	}

	fseek(f, 0, SEEK_END);
	uint32_t fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	if (fsize > 0x2000) {
		/* RAM starts at 0x2000 - 0x3FFF */
		*data_ptr = NULL;
		return 0;
	}

	uint8_t *data = malloc(0x4000);
	fread(data, fsize, 1, f);
	fclose(f);

	*data_ptr = data;
	return 0x4000;
}

