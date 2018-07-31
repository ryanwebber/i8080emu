#include "cpu.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t _step(BloomCPU*);
void _unsupported_opcode(BloomCPU*, uint8_t);
void _debug_instruction(BloomCPU*, const char*, uint8_t);
void _push(BloomCPU*, uint8_t*, uint16_t);

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

uint16_t cpu_mem_get_addr(BloomCPU* cpu, uint16_t offset) {
	return *((uint16_t*) (cpu->memory + cpu->pc + offset));
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
	uint8_t *opcode = &cpu->memory[cpu->pc];
	uint8_t result;
	switch(*opcode) {
		case 0x00: // nop 
			_debug_instruction(cpu, "NOP", 0);
			cpu->pc++;
			break;
		case 0x06: // MVI D |8|
			_debug_instruction(cpu, "MVI D |8|", 1);
			cpu->h = opcode[1];
			cpu->pc++;
			break;
		case 0x11: // lxi d
			_debug_instruction(cpu, "LXI D", 2);
			cpu->d = opcode[1];
			cpu->e = opcode[2];
			cpu->pc++;
			break;
		case 0x1B: // dcx d
			_debug_instruction(cpu, "DCX D", 0);
			{
				uint16_t num = (cpu->e << 8 | cpu->d);
				num--;
				cpu->d = num & 0x00FF;
				cpu->e = (num & 0xFF00) >> 8;
				cpu->pc++;
			}
			break;
		case 0x24: // inr h
			_debug_instruction(cpu, "INR H", 0);
			cpu->h++;
			cpu->pc++;
			break;
		case 0xC3: // jmp
			_debug_instruction(cpu, "JMP", 2);
			cpu->pc = (opcode[2] << 8) | opcode[1];
			break;
		case 0xcd: // call
			_debug_instruction(cpu, "CALL", 2);
			_push(cpu, cpu->memory + cpu->pc + 1, 2);
			cpu->pc = (opcode[2] << 8 | opcode[1]);
			break;
		case 0x31: //lxi sp
			_debug_instruction(cpu, "LXI SP", 2);
			cpu->sp = (opcode[2] << 8) | opcode[1];
			cpu->pc++;
			break;
		default:
			_unsupported_opcode(cpu, *opcode);
			return 1;
	}

	return 0;
}

void cpu_destroy(BloomCPU* cpu) {
	free(cpu->cc);
	free(cpu);
}

void _unsupported_opcode(BloomCPU* cpu, uint8_t opcode) {
	printf("\nUnimplemented instruction:\n0x%04X 0x%02X\n", cpu->pc, opcode);
}

void _debug_instruction(BloomCPU* cpu, const char* inst, uint8_t argc) {
	printf("0x%04X %-16s ; ", cpu->pc, inst);
	for (uint8_t i = 0; i < argc; i++) {
		printf("0x%02X ", cpu->memory[cpu->pc + i + 1]);
	}
	printf("\n");
}

void _push(BloomCPU* cpu, uint8_t *addr, uint16_t len) {
	memcpy(cpu->memory + cpu->sp, addr, len);
	cpu->sp += len;
}

