#include "cpu.h"
#include "instruction/nop.h"
#include "instruction/jmp.h"

#include <stdint.h>
#include <stdio.h>

uint8_t _step(BloomCPU*);
void _unsupported_opcode(BloomCPU*, uint8_t);

BloomCPU* cpu_create() {
	
	ConditionCodes* cc = malloc(sizeof(ConditionCodes));
	
	BloomCPU* cpu = malloc(sizeof(BloomCPU));
	cpu->interruptions_allowed = 1;
	cpu->sp = 0;
	cpu->pc = 0;
	cpu->memory = NULL;
	cpu->size = 0;
	cpu->cc = cc;

	cpu->a = 0;
	cpu->b = 0;
	cpu->c = 0;
	cpu->d = 0;
	cpu->e = 0;
	cpu->h = 0;
	cpu->l = 0;

	return cpu;
}

uint8_t cpu_initialize_rom(BloomCPU* cpu, void* rom_memory, size_t len, uint16_t pc) {
	cpu->memory = rom_memory;
	cpu->pc = pc;
	cpu->size = len;
	return 0;
}

uint8_t cpu_start(BloomCPU* cpu) {
	uint8_t result;
	while (cpu->pc < cpu->size) {
		result = cpu_step(cpu);
		if (result) {
			break;
		}
	}

	printf("\nAborting cpu processing ($pc = 0x%04X, mem_size = %i)...\n", cpu->pc, cpu->size);
	return 0;
}

uint8_t cpu_step(BloomCPU* cpu) {
	uint8_t opcode = cpu->memory[cpu->pc];
	uint8_t result;
	switch(opcode) {
		case 0x00: result = inst_nop(cpu); break;
		case 0xC3: result = inst_jmp(cpu); break;
		default:
			_unsupported_opcode(cpu, opcode);
			result = 1;
	}

	return result;
}

void cpu_destroy(BloomCPU* cpu) {
	free(cpu->cc);
	free(cpu);
}

void _unsupported_opcode(BloomCPU* cpu, uint8_t opcode) {
	printf("\nUnimplemented instruction:\n0x%04X 0x%02X\n", cpu->pc, opcode);
}

