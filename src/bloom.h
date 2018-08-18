#ifndef BLOOM_H
#define BLOOM_H

#include <stdlib.h>
#include <stdint.h>

typedef struct ConditionFlags {
    uint8_t z;
	uint8_t s;
	uint8_t p;
	uint8_t c;
	uint8_t a;
} ConditionFlags;

typedef struct BloomCPU {
	
	uint64_t cycles;

	uint8_t int_enabled;
	uint16_t sp;
	uint16_t pc;
	struct ConditionFlags *flags;

	/* Memory management */
	uint8_t *memory;
	uint16_t mem_lo;
	uint16_t mem_hi;

	/* registers */
	uint8_t a;
	uint8_t b;
	uint8_t c;
	uint8_t d;
	uint8_t e;
	uint8_t h;
	uint8_t l;
} BloomCPU;

BloomCPU* cpu_create(void);
uint8_t   cpu_initialize_rom(BloomCPU*, void* rom_memory, size_t len, uint16_t pc);
uint8_t   cpu_initialize_rwm(BloomCPU*, void* rom_memory, uint16_t mem_lo, uint16_t mem_hi, uint16_t pc);
uint8_t   cpu_start(BloomCPU*);
uint8_t   cpu_step(BloomCPU*);
uint8_t   cpu_interrupt(BloomCPU*, uint8_t interrupt);
void*     cpu_framebuffer(BloomCPU*);
void      cpu_destroy(BloomCPU*);

/* A struct to represent a running machine */
typedef struct BloomMachine BloomMachine;

/* Define a generic object to be passed in callbacks */
typedef void* BloomDelegateRef;

/* Functions that will be used in the delegate */
typedef uint64_t (*FnGetTime)(BloomDelegateRef);
typedef uint8_t (*FnHardwareIn)(BloomDelegateRef, uint8_t port, uint8_t *a);
typedef uint8_t (*FnHardwareOut)(BloomDelegateRef, uint8_t port, uint8_t val);

/* A delegate to call back to a native implementation */
typedef struct BloomMachineDelegate {
	FnGetTime get_time;
	FnHardwareIn data_in;
	FnHardwareOut data_out;

	BloomDelegateRef ref;
} BloomMachineDelegate;

BloomMachine *machine_create(BloomMachineDelegate*, BloomCPU *cpu);
void machine_start(BloomMachine*);
void machine_stop(BloomMachine*);
void machine_destroy(BloomMachine*);

#endif

