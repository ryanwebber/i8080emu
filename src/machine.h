#ifndef MACHINE_H
#define MACHINE_H

#include <stdint.h>
#include "cpu.h"

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

BloomMachine *machine_create(BloomMachineDelegate*, BloomCPU*);
void machine_start(BloomMachine*);
void machine_stop(BloomMachine*);
void machine_destroy(BloomMachine*);

#endif

