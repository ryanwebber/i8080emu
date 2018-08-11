#include "tested/8080emu.h"
#include "../src/cpu.h"
#include "../src/loader.h"

#include <string.h>

State8080 *make_clean(uint8_t *memory, uint16_t len) {
	ConditionCodes cc;
	
	State8080 *cpu = malloc(sizeof(State8080));
	cpu->a = 0;
	cpu->b = 0;
	cpu->c = 0;
	cpu->d = 0;
	cpu->e = 0;
	cpu->h = 0;
	cpu->l = 0;
	cpu->sp = 0;
	cpu->pc = 0;
	cpu->memory = memory;
	cpu->int_enable = 0;
	cpu->cc = cc;

	return cpu;
}

void destroy_clean(State8080 *cpu) {
	free(cpu);
}

uint8_t step_clean(State8080 *cpu) {
	Emulate8080Op(cpu);
	return 0;
}

BloomCPU *make_testing(uint8_t *memory, uint16_t len) {
	BloomCPU* cpu = cpu_create();
	cpu_initialize_rwm(cpu, memory, 0x2000, 0x4000, 0x0);
	return cpu;
}

void destroy_testing(BloomCPU *cpu) {
	cpu_destroy(cpu);
}

uint8_t step_testing(BloomCPU* cpu) {
	return cpu_step(cpu);
}

void print_states(State8080 *cs, BloomCPU *ts) {
	printf("\n---------- Expected State -----------\n");
	printf("{\n");
	printf("\tpc = 0x%04X\n", cs->pc);
	printf("\tsp = 0x%04X\n", cs->sp);
	printf("\ta = 0x%04X\n", cs->a);
	printf("\tb = 0x%04X\n", cs->b);
	printf("\tc = 0x%04X\n", cs->c);
	printf("\td = 0x%04X\n", cs->d);
	printf("\te = 0x%04X\n", cs->e);
	printf("\th = 0x%04X\n", cs->h);
	printf("\tl = 0x%04X\n", cs->l);
	printf("\tflags = {\n");
	printf("\t\tz = %i\n", cs->cc.z);
	printf("\t\ts = %i\n", cs->cc.s);
	printf("\t\tp = %i\n", cs->cc.p);
	printf("\t}\n");
	printf("}\n\n");
	
	printf("\n---------- Expected State -----------\n");
	printf("{\n");
	printf("\tpc = 0x%04X\n", ts->pc);
	printf("\tsp = 0x%04X\n", ts->sp);
	printf("\ta = 0x%04X\n", ts->a);
	printf("\tb = 0x%04X\n", ts->b);
	printf("\tc = 0x%04X\n", ts->c);
	printf("\td = 0x%04X\n", ts->d);
	printf("\te = 0x%04X\n", ts->e);
	printf("\th = 0x%04X\n", ts->h);
	printf("\tl = 0x%04X\n", ts->l);
	printf("\tflags = {\n");
	printf("\t\tz = %i\n", ts->flags->z);
	printf("\t\ts = %i\n", ts->flags->s);
	printf("\t\tp = %i\n", ts->flags->p);
	printf("\t}\n");
	printf("}\n\n");
}
void print_difference(uint8_t inst, const const char* prefix, const char* format, uint16_t expected, uint16_t real) {
	printf("\nAssertion failed for instruction 0x%02X:\n", inst);
	printf("\t[EXPECTED] %s = ", prefix);
	printf(format, expected);
	printf("\n");

	printf("\t[ACTUAL] %s = ", prefix);
	printf(format, real);
	printf("\n");
}

uint8_t assert_state_equal(State8080 *cs, BloomCPU *ts, uint8_t instruction) {
	uint8_t failed = 0;
	
	failed = failed | (cs->pc != ts->pc);
	if (cs->pc != ts->pc) {
		failed = 1;
		print_difference(instruction, "cpu->pc", "0x%04X", cs->pc, ts->pc);
	} else if (cs->sp != ts->sp) {
		failed = 1;
		print_difference(instruction, "cpu->sp", "0x%04X", cs->sp, ts->sp);
	} else if (cs->a != ts->a) {
		failed = 1;
		print_difference(instruction, "cpu->a", "0x%02X", cs->a, ts->a);
	} else if (cs->b != ts->b) {
		failed = 1;
		print_difference(instruction, "cpu->b", "0x%02X", cs->b, ts->b);
	} else if (cs->c != ts->c) {
		failed = 1;
		print_difference(instruction, "cpu->c", "0x%02X", cs->c, ts->c);
	} else if (cs->d != ts->d) {
		failed = 1;
		print_difference(instruction, "cpu->d", "0x%02X", cs->d, ts->d);
	} else if (cs->e != ts->e) {
		failed = 1;
		print_difference(instruction, "cpu->e", "0x%02X", cs->e, ts->e);
	} else if (cs->h != ts->h) {
		failed = 1;
		print_difference(instruction, "cpu->h", "0x%02X", cs->h, ts->h);
	} else if (cs->l != ts->l) {
		failed = 1;
		print_difference(instruction, "cpu->l", "0x%02X", cs->l, ts->l);
	} else if (cs->cc.z != ts->flags->z) {
		failed = 1;
		print_difference(instruction, "cpu->flags->z", "%i", cs->cc.z, ts->flags->z);
	} else if (cs->cc.s != ts->flags->s) {
		failed = 1;
		print_difference(instruction, "cpu->flags->s", "%i", cs->cc.s, ts->flags->s);
	} else if (cs->cc.p != ts->flags->p) {
		failed = 1;
		print_difference(instruction, "cpu->flags->p", "%i", cs->cc.p, ts->flags->p);
	}

	if (failed) {
		print_states(cs, ts);
	}

	return failed;
}

int main(int argc, char *argv[]) {

	if (argc < 2) {
		printf("Usage: %s <rom>\n", argv[0]);
		exit(1);
	}

	uint8_t *rom_data;
	uint32_t size = load(argv[1], &rom_data);
	if (rom_data == NULL || size != 0x4000) {
		printf("Unable to load the file: %s", argv[1]);
		exit(1);
	} else {
		printf("Loaded rom '%s' (%i bytes)\n", argv[1], size);
	}

	/* Clone the address space for the testing executable */
	uint8_t *test_data = malloc(size);
	memcpy(test_data, rom_data, size);

	State8080* clean_state = make_clean(rom_data, size);
	BloomCPU* testing_state = make_testing(test_data, size);

	uint32_t instruction_count = 0;

	while(1) {
		instruction_count++;
		uint8_t instruction = clean_state->memory[clean_state->pc];
		uint16_t pc = clean_state->pc;
		printf("[0x%04X] 0x%02X Stepping...\n", pc, instruction);
		uint8_t result = step_clean(clean_state);
		result = result | step_testing(testing_state);

		if (result) {
			printf("\nError stepping cpu state. Exiting...\n");
			break;
		} else if (assert_state_equal(clean_state, testing_state, instruction)) {
			printf("\n State's diverged after %u instructions. Exiting...\n", instruction_count);
			break;
		}
	}

	destroy_clean(clean_state);
	destroy_testing(testing_state);
	
	free(rom_data);
	free(test_data);

	return 1;
}

