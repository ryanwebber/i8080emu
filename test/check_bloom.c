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

START_TEST(test_bloom_inst_nop)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[1] = {
		0x00
	};
	
	cpu_initialize_rom(cpu, rom, 8, 0);
	
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
	
	cpu_initialize_rom(cpu, rom, 8, 0);
	
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
	
	cpu_initialize_rom(cpu, rom, 24, 0);
	
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
	
	cpu_initialize_rom(cpu, rom, 24, 0);
	
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
	
	cpu_initialize_rom(cpu, rom, 16, 0);
	
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
	
	cpu_initialize_rom(cpu, rom, 16, 0);
	
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
	uint8_t rom[4] = {
		0x24
	};
	
	cpu_initialize_rom(cpu, rom, 24, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->h, 0x1);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_mvi_b)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[4] = {
		0x06, 0x55
	};
	
	cpu_initialize_rom(cpu, rom, 24, 0);
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->b, 0x55);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_ldax_d)
{
	BloomCPU *cpu = cpu_create();
	uint8_t rom[2] = {
		0x1a, 0x55
	};
	
	cpu_initialize_rom(cpu, rom, 8, 0);
	cpu->d = 0x01;
	cpu->e = 0x00;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->a, 0x55);
	
	cpu_destroy(cpu);
}
END_TEST

START_TEST(test_bloom_inst_call)
{
	BloomCPU *cpu = cpu_create();
	uint8_t *rom = malloc(sizeof(uint8_t));
	rom[0] = 0xcd;
	rom[1] = 0xfe;
	rom[2] = 0x55;
	rom[3] = 0x00;
	rom[4] = 0x00;
	
	cpu_initialize_rom(cpu, rom, 60, 0);
	cpu->sp = 4;
	
	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->sp, 0x2);
	ck_assert_uint_eq(cpu->memory[3], 0xFE);
	ck_assert_uint_eq(cpu->memory[4], 0x55);
	
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
	
	cpu_initialize_rom(cpu, rom, 4, 0);
	uint8_t reg[2] = {
		0x32, 0x10
	};

	cpu->d = reg[0];
	cpu->e = reg[1];

	uint8_t result = cpu_step(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->d, reg[0] - 1);
	ck_assert_uint_eq(cpu->e, reg[1]);
	
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
    suite_add_tcase(s, tc_core);

    /* Instructions test case */
    tc_instr = tcase_create("Instructions");

    tcase_add_test(tc_instr, test_bloom_inst_call);
    tcase_add_test(tc_instr, test_bloom_inst_dcx_d);
    tcase_add_test(tc_instr, test_bloom_inst_inr_h);
    tcase_add_test(tc_instr, test_bloom_inst_jmp);
    tcase_add_test(tc_instr, test_bloom_inst_ldax_d);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_d);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_h);
    tcase_add_test(tc_instr, test_bloom_inst_lxi_sp);
    tcase_add_test(tc_instr, test_bloom_inst_mvi_b);
    tcase_add_test(tc_instr, test_bloom_inst_nop);
    tcase_add_test(tc_instr, test_bloom_inst_rim);
	
	suite_add_tcase(s, tc_instr);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = bloom_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

