#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>

#include "../src/cpu.h"
#include "../src/instruction/noop.h"

BloomCPU *cpu;
uint8_t rom[1] = {
	0x0
};

void setup(void){
}

void teardown(void){
}

START_TEST(test_bloom_init)
{
	/* TODO, initialize bloom test */
}
END_TEST

START_TEST(test_bloom_inst_noop)
{
	cpu = cpu_create();
	cpu_initialize_rom(cpu, rom, 8, 0);
	
	uint8_t result = inst_noop(cpu);
	ck_assert_uint_eq(result, 0);
	ck_assert_uint_eq(cpu->pc, 1);
	
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
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, test_bloom_init);
    suite_add_tcase(s, tc_core);

    /* Instructions test case */
    tc_instr = tcase_create("Instructions");
    tcase_add_test(tc_instr, test_bloom_inst_noop);
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

