#include "cpu.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t _step(BloomCPU*);

void _unsupported_opcode(BloomCPU*, uint8_t);
void _debug_instruction(BloomCPU*, const char*, uint8_t);

void _push(BloomCPU*, uint8_t*, uint16_t);
uint8_t* _pop(BloomCPU*, uint8_t);

uint8_t _read_hl(BloomCPU*);
uint8_t _read_de(BloomCPU*);
void _write_hl(BloomCPU*, uint8_t);

ConditionCodes* cc_create() {
	ConditionCodes* cc = malloc(sizeof(ConditionCodes));
	cc->z = 0;
	cc->s = 0;
	cc->p = 0;

	return cc;
}

void cc_destroy(ConditionCodes *cc) {
	free(cc);
}

BloomCPU* cpu_create() {
	
	ConditionCodes *cc = cc_create();
	
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
		case 0x05: //DCR B
			_debug_instruction(cpu, "DCR B", 0);
			cpu->b -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->b);
			break;
		case 0x06: // MVI B
			_debug_instruction(cpu, "MVI B", 1);
			cpu->b = opcode[1];
			cpu->pc += 2;
			break;
		case 0x0d: //DCR C
			_debug_instruction(cpu, "DCR C", 0);
			cpu->c -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->c);
			break;
		case 0x11: // lxi d
			_debug_instruction(cpu, "LXI D", 2);
			cpu->d = opcode[1];
			cpu->e = opcode[2];
			cpu->pc += 3;
			break;
		case 0x13: // inx d
			_debug_instruction(cpu, "INX D", 0);
			{
				uint16_t num = (cpu->d << 8 | cpu->e) + 1;
				cpu->d = (num & 0xFF00) >> 8;
				cpu->e = num & 0x0FF;
				cpu->pc++;
			}
			break;
		case 0x15: //DCR D
			_debug_instruction(cpu, "DCR D", 0);
			cpu->d -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->d);
			break;
		case 0x1a: // ldax d
			_debug_instruction(cpu, "LDAX D", 0);
			cpu->a = _read_de(cpu);
			cpu->pc++;
			break;
		case 0x1b: // dcx d
			_debug_instruction(cpu, "DCX D", 0);
			{
				uint16_t num = (cpu->d << 8 | cpu->e) - 1;
				cpu->d = (num & 0xFF00) >> 8;
				cpu->e = num & 0x00FF;
				cpu->pc++;
			}
			break;
		case 0x20: // rim
			_debug_instruction(cpu, "RIM", 0);
			/* Serial instruction, ignore */
			cpu->pc++;
			break;
		case 0x21: // lxi h
			_debug_instruction(cpu, "LXI H", 2);
			cpu->h = opcode[1];
			cpu->l = opcode[2];
			cpu->pc += 3;
			break;
		case 0x23: // inx h
			_debug_instruction(cpu, "INX H", 0);
			{
				uint16_t num = (cpu->h << 8 | cpu->l) + 1;
				cpu->h = (num & 0xFF00) >> 8;
				cpu->l = num & 0x0FF;
				cpu->pc++;
			}
			break;
		case 0x24: // inr h
			_debug_instruction(cpu, "INR H", 0);
			cpu->h++;
			cpu->pc++;
			_update_flags(cpu, cpu->h);
			break;
		case 0x31: //lxi sp
			_debug_instruction(cpu, "LXI SP", 2);
			cpu->sp = (opcode[2] << 8) | opcode[1];
			cpu->pc += 3;
			break;
		case 0x32: // sta
			_debug_instruction(cpu, "STA", 2);
			cpu->memory[opcode[2] << 8 | opcode[1]] = cpu->a;
			cpu->pc += 3;
			break;
		case 0x4e: // mov c,m
			_debug_instruction(cpu, "MOV A<-M", 0);
			cpu->c = _read_hl(cpu);
			cpu->pc++;
			break;
		case 0x56: // mov d,m
			_debug_instruction(cpu, "MOV D<-M", 0);
			cpu->d = _read_hl(cpu);
			cpu->pc++;
			break;
		case 0x58: // mov e,b
			_debug_instruction(cpu, "MOV E<-B", 0);
			cpu->e = cpu->b;
			cpu->pc++;
			break;
		case 0x5e: // mov e,m
			_debug_instruction(cpu, "MOV E<-M", 0);
			cpu->e = _read_hl(cpu);
			cpu->pc++;
			break;
		case 0x77: // mov m,a
			_debug_instruction(cpu, "MOV M<-A", 0);
			_write_hl(cpu, cpu->a);
			cpu->pc++;
			break;
		case 0x7e: // mov a,m
			_debug_instruction(cpu, "MOV A<-M", 0);
			cpu->a = _read_hl(cpu);
			cpu->pc++;
			break;
		case 0xc2: // jnz
			_debug_instruction(cpu, "JNZ", 2);
			if (cpu->cc->z == 0) {
				cpu->pc = (opcode[2] << 8) | opcode[1];
			} else {
				cpu->pc++;
			}
			break;
		case 0xc3: // jmp
			_debug_instruction(cpu, "JMP", 2);
			cpu->pc = (opcode[2] << 8) | opcode[1];
			break;
		case 0xcd: // call
			_debug_instruction(cpu, "CALL", 2);
			_push(cpu, cpu->memory + cpu->pc + 1, 2);
			cpu->pc = (opcode[2] << 8 | opcode[1]);
			break;
		case 0xc9: // ret
			_debug_instruction(cpu, "RET", 0);
			{
				uint8_t *addr = _pop(cpu, 2);
				cpu->pc = (addr[1] << 8 | addr[0]);
			}
			break;
		default:
			_unsupported_opcode(cpu, *opcode);
			return 1;
	}

	return 0;
}

void cpu_destroy(BloomCPU* cpu) {
	cc_destroy(cpu->cc);
	free(cpu);
}

void _unsupported_opcode(BloomCPU* cpu, uint8_t opcode) {
	printf("\nUnimplemented instruction:\n0x%04X 0x%02X\n", cpu->pc, opcode);
}

void _debug_instruction(BloomCPU* cpu, const char* inst, uint8_t argc) {
	printf("0x%04X 0x%02X %-16s ; ", cpu->pc, cpu->memory[cpu->pc], inst);
	for (uint8_t i = 0; i < argc; i++) {
		printf("0x%02X ", cpu->memory[cpu->pc + i + 1]);
	}
	printf("\n");
}

uint8_t _parity(uint8_t val) {
	uint8_t c = 0;
	for(uint8_t i = 0; i < sizeof(val) * 8; i++) {
		c += (val >> i) & 0x01;
	}
	return c % 2 == 0;
}

void _update_flags(BloomCPU* cpu, uint8_t val) {
	// zero flag
	cpu->cc->z = (val == 0);
	
	// sign flag
	cpu->cc->s = (val & 0x80) == 0x80;
	
	// parity flag
	cpu->cc->p = _parity(val);
}

void _push(BloomCPU* cpu, uint8_t *addr, uint16_t len) {
	cpu->sp -= len;
	memcpy(cpu->memory + cpu->sp, addr, len);
}

uint8_t* _pop(BloomCPU* cpu, uint8_t len) {
	uint8_t *addr = cpu->memory + cpu->sp;
	cpu->sp += len;
	return addr;
}

uint8_t _read_hl(BloomCPU* cpu) {
	return cpu->memory[cpu->h << 8 | cpu->l];
}

uint8_t _read_de(BloomCPU* cpu) {
	return cpu->memory[cpu->d << 8 | cpu->e];
}

void _write_hl(BloomCPU* cpu, uint8_t val) {
	cpu->memory[cpu->h << 8 | cpu->l] = val;
}

