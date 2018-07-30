#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include <stdint.h>

typedef struct ConditionCodes {
    //uint8_t z:1;
	//uint8_t s:1;
	//uint8_t p:1;
	//uint8_t cy:1;
	//uint8_t ac:1;
	//uint8_t pad:3;
} ConditionCodes;

typedef struct BloomCPU {
	uint8_t interruptions_allowed;
	uint16_t sp;
	uint16_t pc;
	uint8_t *memory;
	uint16_t size;
	struct ConditionCodes *cc;

	/* registers */
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
} BloomCPU;

BloomCPU* cpu_create();
uint8_t   cpu_initialize_rom(BloomCPU*, void* rom_memory, size_t len, uint16_t pc);
uint8_t   cpu_start(BloomCPU*);
uint8_t   cpu_step(BloomCPU*);
void      cpu_destroy(BloomCPU*);

#endif

