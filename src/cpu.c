#include "cpu.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t _step(BloomCPU*);

void _unsupported_opcode(BloomCPU*, uint8_t);
void _debug_instruction(BloomCPU*, const char*, uint8_t);

void _push(BloomCPU*, uint8_t*, uint16_t);
uint8_t* _pop(BloomCPU*, uint8_t);

uint8_t* _read_mem(BloomCPU*, uint8_t hi, uint8_t lo);
uint8_t _write_mem(BloomCPU*, uint8_t);

int i = 0;

ConditionFlags* cf_create() {
	ConditionFlags* cf = malloc(sizeof(ConditionFlags));
	cf->z = 0;
	cf->s = 0;
	cf->p = 0;
	cf->c = 0;
	cf->a = 0;

	return cf;
}

void cf_destroy(ConditionFlags *cf) {
	free(cf);
}

BloomCPU* cpu_create() {
	
	ConditionFlags *cf = cf_create();
	
	BloomCPU* cpu = malloc(sizeof(BloomCPU));
	cpu->int_enabled = 1;
	cpu->sp = 0;
	cpu->pc = 0;
	cpu->flags = cf;
	
	cpu->memory = NULL;
	cpu->mem_hi = 0;
	cpu->mem_lo = 0;

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

	/* Create a non-writable address space */
	cpu->mem_lo = 0x00;
	cpu->mem_hi = 0x00;
	
	return 0;
}

uint8_t cpu_initialize_rwm(BloomCPU *cpu, void* rom_memory, uint16_t mem_lo, uint16_t mem_hi, uint16_t pc) {
	cpu->memory = rom_memory;
	cpu->pc = pc;

	/* Create a partially-writable address space */
	cpu->mem_lo = mem_lo;
	cpu->mem_hi = mem_hi;
	
	return 0;
}

uint8_t cpu_start(BloomCPU* cpu) {
	uint8_t result;
	while (1) {
		result = cpu_step(cpu);
		if (result) {
			break;
		}
	}

	printf("\nAborting cpu processing ($pc = 0x%04X, cycles = %i)...\n", cpu->pc, i);
	return 0;
}

uint8_t cpu_step(BloomCPU* cpu) {
	uint8_t *opcode = &cpu->memory[cpu->pc];
	uint8_t result = 0;
	switch(*opcode) {
		case 0x00: // nop 
			_debug_instruction(cpu, "NOP", 0);
			cpu->pc++;
			break;
		case 0x01: // lxi b
			_debug_instruction(cpu, "LXI B", 2);
			cpu->b = opcode[2];
			cpu->c = opcode[1];
			cpu->pc += 3;
			break;
		case 0x05: // dcr b
			_debug_instruction(cpu, "DCR B", 0);
			cpu->b -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->b);
			break;
		case 0x06: // mvi b
			_debug_instruction(cpu, "MVI B", 1);
			cpu->b = opcode[1];
			cpu->pc += 2;
			break;
		case 0x09: // dad b
			_debug_instruction(cpu, "DAD B", 0);
			{
				uint32_t num = (cpu->b << 8 | cpu->c) + (cpu->h << 8 | cpu -> l);
				cpu->h = (num & 0x0000FF00) >> 8;
				cpu->l = (num & 0x000000FF);
				cpu->flags->c = num > 0x0000FFFF;
				cpu->pc++;
			}
			break;
		case 0x0d: // dcr c
			_debug_instruction(cpu, "DCR C", 0);
			cpu->c -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->c);
			break;
		case 0x0e: //mvi c
			_debug_instruction(cpu, "MVI C", 1);
			cpu->c = opcode[1];
			cpu->pc += 2;
			break;
		case 0x0f: // rrc
			_debug_instruction(cpu, "RRC", 0);
			cpu->a = ((cpu->a & 0x01) << 7) | (cpu->a >> 1);
			cpu->flags->c = (cpu->a & 0x80) >> 7;
			cpu->pc++;
			break;
		case 0x11: // lxi d
			_debug_instruction(cpu, "LXI D", 2);
			cpu->d = opcode[2];
			cpu->e = opcode[1];
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
		case 0x15: // dcr d
			_debug_instruction(cpu, "DCR D", 0);
			cpu->d -= 1;
			cpu->pc++;
			_update_flags(cpu, cpu->d);
			break;
		case 0x19: // dad d
			_debug_instruction(cpu, "DAD D", 0);
			{
				uint32_t num = (cpu->d << 8 | cpu->e) + (cpu->h << 8 | cpu -> l);
				cpu->h = (num & 0x0000FF00) >> 8;
				cpu->l = (num & 0x000000FF);
				cpu->flags->c = num > 0x0000FFFF;
				cpu->pc++;
			}
			break;
		case 0x1a: // ldax d
			_debug_instruction(cpu, "LDAX D", 0);
			cpu->a = _read_mem(cpu, cpu->d, cpu->e)[0];
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
			cpu->h = opcode[2];
			cpu->l = opcode[1];
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
		case 0x26: // mvi h
			_debug_instruction(cpu, "MVI_H", 1);
			cpu->h = opcode[1];
			cpu->pc += 2;
			break;
		case 0x29: // dad h
			_debug_instruction(cpu, "DAD H", 0);
			{
				uint16_t num = (cpu->h << 8 | cpu->l);
				cpu->h = ((num << 1) & 0xFF00) >> 8;
				cpu->l = num << 1 & 0x00FF;
				cpu->flags->c = ((num >> 15) & 0x01) == 0x01;
				cpu->pc++;
			}
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
		case 0x36: // mvi m
			_debug_instruction(cpu, "MVI M", 1);
			cpu->pc += 2;
			result = _write_mem(cpu, opcode[1]);
			break;
		case 0x3a: // lda
			_debug_instruction(cpu, "LDA", 2);
			cpu->a = _read_mem(cpu, opcode[2], opcode[1])[0];
			cpu->pc += 3;
			break;
		case 0x3e: // mvi a
			_debug_instruction(cpu, "MVI A", 1);
			cpu->a = opcode[1];
			cpu->pc += 2;
			break;
		case 0x4e: // mov c,m
			_debug_instruction(cpu, "MOV A<-M", 0);
			cpu->c = _read_mem(cpu, cpu->h, cpu->l)[0];
			cpu->pc++;
			break;
		case 0x56: // mov d,m
			_debug_instruction(cpu, "MOV D<-M", 0);
			cpu->d = _read_mem(cpu, cpu->h, cpu->l)[0];
			cpu->pc++;
			break;
		case 0x58: // mov e,b
			_debug_instruction(cpu, "MOV E<-B", 0);
			cpu->e = cpu->b;
			cpu->pc++;
			break;
		case 0x5e: // mov e,m
			_debug_instruction(cpu, "MOV E<-M", 0);
			cpu->e = _read_mem(cpu, cpu->h, cpu->l)[0];
			cpu->pc++;
			break;
		case 0x66: // mov h,m
			cpu->h = _read_mem(cpu, cpu->h, cpu->l)[0];
			cpu->pc++;
			break;
		case 0x6f: // mov l,a
			_debug_instruction(cpu, "MOV L<-A", 0);
			cpu->l = cpu->a;
			cpu->pc++;
			break;
		case 0x77: // mov m,a
			_debug_instruction(cpu, "MOV M<-A", 0);
			cpu->pc++;
			result = _write_mem(cpu, cpu->a);
			break;
		case 0x7a: // mov a,d
			_debug_instruction(cpu, "MOV A<-D", 0);
			cpu->a = cpu->d;
			cpu->pc++;
			break;
		case 0x7b: // mov a,e
			_debug_instruction(cpu, "MOV A<-E", 0);
			cpu->a = cpu->e;
			cpu->pc++;
			break;
		case 0x7c: // mov a,h
			_debug_instruction(cpu, "MOV A<-H", 0);
			cpu->a = cpu->h;
			cpu->pc++;
			break;
		case 0x7e: // mov a,m
			_debug_instruction(cpu, "MOV A<-M", 0);
			cpu->a = _read_mem(cpu, cpu->h, cpu->l)[0];
			cpu->pc++;
			break;
		case 0xa7: // ana a
			_debug_instruction(cpu, "ANA A", 0);
			cpu->flags->c = 0;
			cpu->pc++;
			_update_flags(cpu, cpu->a);
			break;
		case 0xaf: // xra a
			_debug_instruction(cpu, "XRA A", 0);
			cpu->a = 0;
			cpu->flags->c = 0;
			_update_flags(cpu, cpu->a);
			cpu->pc++;
			break;
		case 0xc1: // pop b
			_debug_instruction(cpu, "POP B", 0);
			{
				uint8_t *addr = _pop(cpu, 2);
				cpu->b = addr[1];
				cpu->c = addr[0];
				cpu->pc++;
			}
			break;
		case 0xc2: // jnz
			_debug_instruction(cpu, "JNZ", 2);
			if (cpu->flags->z == 0) {
				cpu->pc = (opcode[2] << 8) | opcode[1];
			} else {
				cpu->pc += 3;
			}
			break;
		case 0xc3: // jmp
			_debug_instruction(cpu, "JMP", 2);
			cpu->pc = (opcode[2] << 8) | opcode[1];
			break;
		case 0xc5: // push b
			_debug_instruction(cpu, "PUSH B", 0);
			_push(cpu, &cpu->b, 1);
			_push(cpu, &cpu->c, 1);
			cpu->pc++;
			break;
		case 0xc6: // adi
			_debug_instruction(cpu, "ADI", 1);
			{
				uint16_t val = cpu->a + opcode[1];
				cpu->a = val & 0xFF;
				cpu->flags->c = val > 0xFF;
				cpu->pc += 2;
				_update_flags(cpu, cpu->a);
			}
			break;
		case 0xcd: // call
			_debug_instruction(cpu, "CALL", 2);
			{
				uint16_t addr = cpu->pc + 3;
				_push(cpu, (uint8_t*) &addr, 2);
				cpu->pc = (opcode[2] << 8 | opcode[1]);
			}
			break;
		case 0xc9: // ret
			_debug_instruction(cpu, "RET", 0);
			{
				uint8_t *addr = _pop(cpu, 2);
				cpu->pc = (addr[1] << 8 | addr[0]);
			}
			break;
		case 0xd1: // pop d
			_debug_instruction(cpu, "POP D", 0);
			{
				uint8_t *addr = _pop(cpu, 2);
				cpu->d = addr[1];
				cpu->e = addr[0];
				cpu->pc++;
			}
			break;
		case 0xd3: // out
			_debug_instruction(cpu, "OUT", 0);
			cpu->pc += 2;
			break;
		case 0xd5: // push d 
			_debug_instruction(cpu, "PUSH D", 0);
			_push(cpu, &cpu->d, 1);
			_push(cpu, &cpu->e, 1);
			cpu->pc++;
			break;
		case 0xe1: // pop h
			_debug_instruction(cpu, "POP H", 0);
			{
				uint8_t *addr = _pop(cpu, 2);
				cpu->h = addr[1];
				cpu->l = addr[0];
				cpu->pc++;
			}
			break;
		case 0xe5: // push h
			_debug_instruction(cpu, "PUSH H", 0);
			_push(cpu, &cpu->h, 1);
			_push(cpu, &cpu->l, 1);
			cpu->pc++;
			break;
		case 0xe6: // ani
			_debug_instruction(cpu, "ANI", 1);
			cpu->a = cpu->a & opcode[1];
			cpu->flags->c = 0;
			_update_flags(cpu, cpu->a);
			cpu->pc += 2;
			break;
		case 0xeb: // xchg
			_debug_instruction(cpu, "XCHG", 0);
			{
				uint8_t thi = cpu->h;
				uint8_t tlo = cpu->l;
				cpu->h = cpu->d;
				cpu->l = cpu->e;
				cpu->d = thi;
				cpu->e = tlo;
				cpu->pc++;
			}
			break;
		case 0xf1: // pop psw
			_debug_instruction(cpu, "POP PSW", 0);
			{
				uint8_t flags = _pop(cpu, 1)[0];
				uint8_t val = _pop(cpu, 1)[0];
				cpu->flags->z = (flags & 0x01) > 0;
				cpu->flags->s = (flags & 0x02) > 0;
				cpu->flags->p = (flags & 0x04) > 0;
				cpu->flags->c = (flags & 0x08) > 0;
				cpu->flags->a = (flags & 0x10) > 0;
				cpu->a = val;
				cpu->pc++;
			}
			break;
		case 0xf5: // push psw
			_debug_instruction(cpu, "PUSH PSW", 0);
			{
				uint8_t flags = 0x00;
				flags |= (cpu->flags->z & 0x1) << 0;
				flags |= (cpu->flags->s & 0x1) << 1;
				flags |= (cpu->flags->p & 0x1) << 2;
				flags |= (cpu->flags->c & 0x1) << 3;
				flags |= (cpu->flags->a & 0x1) << 4;
				_push(cpu, &cpu->a, 1);
				_push(cpu, &flags, 1);
				cpu->pc++;
			}
			break;
		case 0xfb: // ei
			_debug_instruction(cpu, "EI", 0);
			cpu->int_enabled = 1;
			cpu->pc++;
			break;
		case 0xfe: // cpi
			_debug_instruction(cpu, "CPI", 1);
			_update_flags(cpu, cpu->a - opcode[1]);
			cpu->flags->c = opcode[1] > cpu->a;
			cpu->pc += 2;
			break;
		default:
			_unsupported_opcode(cpu, *opcode);
			result = 1;
	}

	i++;
	return result;
}

void cpu_destroy(BloomCPU* cpu) {
	cf_destroy(cpu->flags);
	free(cpu);
}

void _unsupported_opcode(BloomCPU* cpu, uint8_t opcode) {
	printf("\nUnimplemented instruction:\n0x%04X 0x%02X\n\n", cpu->pc, opcode);
}

void _debug_instruction(BloomCPU* cpu, const char* inst, uint8_t argc) {
	printf("[0x%04X]    0x%02X %-16s ; ", cpu->pc, cpu->memory[cpu->pc], inst);
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
	cpu->flags->z = (val == 0);
	
	// sign flag
	cpu->flags->s = (val & 0x80) == 0x80;
	
	// parity flag
	cpu->flags->p = _parity(val);
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

uint8_t* _read_mem(BloomCPU* cpu, uint8_t hi_addr, uint8_t lo_addr) {
	return cpu->memory + (hi_addr << 8 | lo_addr);
}

uint8_t _write_mem(BloomCPU* cpu, uint8_t val) {
	uint16_t offset = cpu->h << 8 | cpu->l;
	if (offset >= cpu->mem_hi || offset < cpu->mem_lo) {
		printf("\nInvalid memory write: 0x%02X -> memory[0x%04X]\n", val, offset);
		printf("ERROR - detected invalid write address. Aborting...\n");
		return 1;
	}

	cpu->memory[offset] = val;
	return 0;
}

