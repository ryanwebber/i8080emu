#include "loader.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t load(const char* filename, uint8_t **data_ptr) {

	FILE *f = fopen(filename, "rb");
	
	if (f != NULL) {
		fseek(f, 0, SEEK_END);
		uint32_t fsize = ftell(f);
		fseek(f, 0, SEEK_SET);

		uint8_t *data = malloc(fsize);
		fread(data, fsize, 1, f);
		fclose(f);

		*data_ptr = data;
		return fsize;
	} else {
		*data_ptr = NULL;
		return 0;
	}
}

