#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>

#include "../src/cpu.h"

START_TEST(test_bloom_init)
{
	/* TODO, initialize bloom test */
}
END_TEST


START_TEST(test_bloom_flags)
	BloomCPU *cpu = cpu_create();
	cpu_initialize_rom(cpu, NULL, 0, 0);
	
	// test zero bit set
	_update_flags(cpu, 0x00);
	ck_assert_uint_eq(cpu->cc->z, 1);

	// test zero bit unset
	_update_flags(cpu, 0x01);
	ck_assert_uint_eq(cpu->cc->z, 0);

	// test sign bit set
	_update_flags(cpu, 0xF0);
	ck_assert_uint_eq(cpu->cc->s, 1);

	// test sign bit unset
	_update_flags(cpu, 0x0F);
	ck_assert_uint_eq(cpu->cc->s, 0);

	// test parity bit set
	_update_flags(cpu, 0x7D);
	ck_assert_uint_eq(cpu->cc->p, 1);

	// test parity bit unset
	_update_flags(cpu, 0x7C);
	ck_assert_uint_eq(cpu->cc->p, 0);

	cpu_destroy(cpu);
END_TEST


///////////////////////////////////////////////
//             Instruction Tests             //
///////////////////////////////////////////////

START_TEST(test_bloom_inst_nop)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x00
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 1);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_rim)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x20
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 1);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_jmp)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[4] = {
		0xC3, 0xFF, 0xFE, 0x66
	};
	
	cpu_initialize_rom(cpu, rom, 4, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 0xFEFF);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_lxi_sp)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[4] = {
		0x31, 0xFF, 0xFE, 0x66
	};
	
	cpu_initialize_rom(cpu, rom, 4, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->sp, 0xFEFF);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_lxi_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[3] = {
		0x11, 0xFF, 0xFE
	};
	
	cpu_initialize_rom(cpu, rom, 3, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, 0xFF);
	ck_assert_uint_eq(cpu->e, 0xFE);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_lxi_h)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[3] = {
		0x21, 0xFF, 0xFE
	};
	
	cpu_initialize_rom(cpu, rom, 3, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->h, 0xFF);
	ck_assert_uint_eq(cpu->l, 0xFE);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_inr_h)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x24
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->h, 0x1);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mvi_b)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x06, 0x55
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->b, 0x55);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_m_a)
{
	uint8_t *rom = malloc(sizeof(uint8_t) * 2);
	BloomCPU *cpu = cpu_create();
	rom[0] = 0x77;
	rom[1] = 0x0;
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x0;
	cpu->l = 0x1;
	cpu->a = 0x98;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(rom[1], 0x98);
	
	cpu_destroy(cpu);
	free(rom);
}
END_TEST

START_TEST(test_bloom_inst_ldax_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x1a, 0x55
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->d = 0x00;
	cpu->e = 0x01;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->a, 0x55);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_ret)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[3] = {
		0xc9, 0x99, 0x88
	};
	
	cpu_initialize_rom(cpu, rom, 3, 0);
	cpu->sp = 0x0001;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 0x8899);
	ck_assert_uint_eq(cpu->sp, 0x0003);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_e_b)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x58
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->b = 0x99;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->e, 0x99);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_e_m)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x5e, 0x77
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->e, 0x77);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_a_m)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x7e, 0x77
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->a, 0x77);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_c_m)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x4e, 0x77
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->c, 0x77);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mov_d_m)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x56, 0x77
	};
	
	cpu_initialize_rom(cpu, rom, 2, 0);
	cpu->h = 0x00;
	cpu->l = 0x01;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, 0x77);

	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_call)
{
	BloomCPU *cpu = cpu_create();
	uint8_t *rom = malloc(sizeof(uint8_t) * 5);
	rom[0] = 0xcd;
	rom[1] = 0xfe;
	rom[2] = 0x55;
	rom[3] = 0x00;
	rom[4] = 0x00;
	
	cpu_initialize_rom(cpu, rom, 5, 0);
	cpu->sp = 5;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->sp, 0x3);
	ck_assert_uint_eq(cpu->memory[3], 0xFE);
	ck_assert_uint_eq(cpu->memory[4], 0x55);
	
	cpu_destroy(cpu);
	free(rom);
}
END_TEST

START_TEST(test_bloom_inst_sta)
{
	BloomCPU *cpu = cpu_create();
	uint8_t *rom = malloc(sizeof(uint8_t) * 4);
	rom[0] = 0x32;
	rom[1] = 0x03;
	rom[2] = 0x00;
	rom[3] = 0x00;
	
	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->a = 0x56;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->memory[3], 0x56);
	
	cpu_destroy(cpu);
	free(rom);
}
END_TEST

START_TEST(test_bloom_inst_dcx_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x1B
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->d = 0x32;
	cpu->e = 0x10;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, 0x32);
	ck_assert_uint_eq(cpu->e, 0x0F);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_inx_h)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x23
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->h = 0x55;
	cpu->l = 0x66;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->h, 0x55);
	ck_assert_uint_eq(cpu->l, 0x67);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_inx_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x23
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->d = 0x55;
	cpu->e = 0x66;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, 0x55);
	ck_assert_uint_eq(cpu->e, 0x67);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_dcr_b)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x05
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->b = 0x99;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->b, 0x98);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_dcr_c)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x0d
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->c = 0x99;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->c, 0x98);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_dcr_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x15
	};
	
	cpu_initialize_rom(cpu, rom, 1, 0);
	cpu->d = 0x99;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, 0x98);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_jnz)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[4] = {
		0xC2, 0xC2, 0xFE, 0xFF
	};
	
	cpu_initialize_rom(cpu, rom, 4, 0);
	cpu->cc->z = 1;

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 1);

	cpu->cc->z = 0;
	result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 0xFFFE);
	
	cpu_destroy(cpu);
}
END_TEST


Suite* bloom_suite(void){
    Suite *s;
    TCase *tc_core;
    TCase *tc_instr;

    s = suite_create("Bloom");

    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_bloom_init);
    tcase_add_test(tc_core, test_bloom_flags);
    suite_add_tcase(s, tc_core);

    /* Instructions test case */
    tc_instr = tcase_create("Instructions");

    tcase_add_test(tc_instr, test_bloom_inst_call);
    tcase_add_test(tc_instr, test_bloom_inst_dcr_b);
    tcase_add_test(tc_instr, test_bloom_inst_dcr_c);
    tcase_add_test(tc_instr, test_bloom_inst_dcr_d);
    tcase_add_test(tc_instr, test_bloom_inst_dcx_d);
    tcase_add_test(tc_instr, test_bloom_inst_inr_h);
    tcase_add_test(tc_instr, test_bloom_inst_inx_h);
    tcase_add_test(tc_instr, test_bloom_inst_jmp);
    tcase_add_test(tc_instr, test_bloom_inst_jnz);
    tcase_add_test(tc_instr, test_bloom_inst_ldax_d);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_d);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_h);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_sp);
    tcase_add_test(tc_instr, test_bloom_inst_mvi_b);
    tcase_add_test(tc_instr, test_bloom_inst_mov_a_m);
    tcase_add_test(tc_instr, test_bloom_inst_mov_c_m);
    tcase_add_test(tc_instr, test_bloom_inst_mov_d_m);
    tcase_add_test(tc_instr, test_bloom_inst_mov_d_m);
    tcase_add_test(tc_instr, test_bloom_inst_mov_e_b);
    tcase_add_test(tc_instr, test_bloom_inst_mov_e_m);
    tcase_add_test(tc_instr, test_bloom_inst_mov_m_a);
    tcase_add_test(tc_instr, test_bloom_inst_nop);
    tcase_add_test(tc_instr, test_bloom_inst_ret);
    tcase_add_test(tc_instr, test_bloom_inst_rim);
    tcase_add_test(tc_instr, test_bloom_inst_sta);
	
	suite_add_tcase(s, tc_instr);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = bloom_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

