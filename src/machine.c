#include "machine.h"
#include "cpu.h"

#include <stdio.h>
#include <unistd.h>

#define STATE_STOPPED 0x00
#define STATE_STARTED 0x01

struct BloomMachine {
	BloomCPU *cpu;
	BloomMachineDelegate *delegate;

	uint8_t volatile state;
};



/** API Implementation **/

BloomMachine *machine_create(BloomMachineDelegate *delegate, BloomCPU *cpu) {
	BloomMachine *machine = malloc(sizeof(BloomMachine));
	machine->cpu = cpu;
	machine->delegate = delegate;
	machine->state = STATE_STOPPED;

	return machine;
}

void machine_start(BloomMachine *machine) {
	machine->state = STATE_STARTED;
	BloomDelegateRef ref = machine->delegate->ref;

	printf("--- Starting machine execution!\n");

	uint64_t now;
	uint64_t last_cycle = machine->delegate->get_time(ref);
	uint64_t next_interrupt = last_cycle + 16000.0;
	uint64_t last_interrupt = last_cycle;
	uint8_t interrupt = 0;

	while (machine->state == STATE_STARTED) {
		now = machine->delegate->get_time(ref);

		if (machine->cpu->int_enabled && now > next_interrupt) {
			//("--- Generating interrupt (interrupt=%d)\n", interrupt + 1);
			cpu_interrupt(machine->cpu, interrupt + 1);
			interrupt = (interrupt + 1) % 2;
			next_interrupt = now + 8000;
		}

		/* at 2MZHz, we do 2 cycles per microsecond */
		cpu_reset_cycles(machine->cpu);
		uint64_t elapsed = now - last_cycle;
		uint64_t run_until = machine->cpu->cycles + (elapsed * 2);
		//printf("--- Running batch of %llu cycles\n", run_until - machine->cpu->cycles);

		while (machine->cpu->cycles < run_until) {
			uint8_t *opcode = machine->cpu->memory + machine->cpu->pc;
			uint8_t result = 0;
			switch (*opcode) {
				case 0xdb: // IN
					result = machine->delegate->data_in(ref, opcode[1], &machine->cpu->a);
					machine->cpu->pc += 2;
					machine->cpu->cycles += 3;
				case 0xd3: // OUT
					result = machine->delegate->data_out(ref, opcode[1], machine->cpu->a);
					machine->cpu->pc += 2;
					machine->cpu->cycles += 3;
				default:
					result = cpu_step(machine->cpu);
			}

			if (result) {
				machine->state = STATE_STOPPED;
				break;
			}
		}

		usleep(1000L);
		last_cycle = now;
	}
}

void machine_stop(BloomMachine *machine) {
	machine->state = STATE_STOPPED;
}

void machine_destroy(BloomMachine *machine) {
	free(machine);
}

