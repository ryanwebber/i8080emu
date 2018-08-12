#include <stdio.h>
#include <stdint.h>
#include "../src/cpu.h"

#include "instructions/test_instruction_aci.h"
#include "instructions/test_instruction_adc_a.h"
#include "instructions/test_instruction_adc_b.h"
#include "instructions/test_instruction_adc_c.h"
#include "instructions/test_instruction_adc_d.h"
#include "instructions/test_instruction_adc_e.h"
#include "instructions/test_instruction_adc_h.h"
#include "instructions/test_instruction_adc_l.h"
#include "instructions/test_instruction_adc_m.h"
#include "instructions/test_instruction_add_a.h"
#include "instructions/test_instruction_add_b.h"
#include "instructions/test_instruction_add_c.h"
#include "instructions/test_instruction_add_d.h"
#include "instructions/test_instruction_add_e.h"
#include "instructions/test_instruction_add_h.h"
#include "instructions/test_instruction_add_l.h"
#include "instructions/test_instruction_add_m.h"
#include "instructions/test_instruction_adi.h"
#include "instructions/test_instruction_ana_a.h"
#include "instructions/test_instruction_ana_b.h"
#include "instructions/test_instruction_ana_c.h"
#include "instructions/test_instruction_ana_d.h"
#include "instructions/test_instruction_ana_e.h"
#include "instructions/test_instruction_ana_h.h"
#include "instructions/test_instruction_ana_l.h"
#include "instructions/test_instruction_ana_m.h"
#include "instructions/test_instruction_ani.h"
#include "instructions/test_instruction_call_adr.h"
#include "instructions/test_instruction_cc_adr.h"
#include "instructions/test_instruction_cm_adr.h"
#include "instructions/test_instruction_cma.h"
#include "instructions/test_instruction_cmc.h"
#include "instructions/test_instruction_cmp_a.h"
#include "instructions/test_instruction_cmp_b.h"
#include "instructions/test_instruction_cmp_c.h"
#include "instructions/test_instruction_cmp_d.h"
#include "instructions/test_instruction_cmp_e.h"
#include "instructions/test_instruction_cmp_h.h"
#include "instructions/test_instruction_cmp_l.h"
#include "instructions/test_instruction_cmp_m.h"
#include "instructions/test_instruction_cnc_adr.h"
#include "instructions/test_instruction_cnz_adr.h"
#include "instructions/test_instruction_cp_adr.h"
#include "instructions/test_instruction_cpe_adr.h"
#include "instructions/test_instruction_cpi.h"
#include "instructions/test_instruction_cpo_adr.h"
#include "instructions/test_instruction_cz_adr.h"
#include "instructions/test_instruction_daa.h"
#include "instructions/test_instruction_dad_b.h"
#include "instructions/test_instruction_dad_d.h"
#include "instructions/test_instruction_dad_h.h"
#include "instructions/test_instruction_dad_sp.h"
#include "instructions/test_instruction_dcr_a.h"
#include "instructions/test_instruction_dcr_b.h"
#include "instructions/test_instruction_dcr_c.h"
#include "instructions/test_instruction_dcr_d.h"
#include "instructions/test_instruction_dcr_e.h"
#include "instructions/test_instruction_dcr_h.h"
#include "instructions/test_instruction_dcr_l.h"
#include "instructions/test_instruction_dcr_m.h"
#include "instructions/test_instruction_dcx_b.h"
#include "instructions/test_instruction_dcx_d.h"
#include "instructions/test_instruction_dcx_h.h"
#include "instructions/test_instruction_dcx_sp.h"
#include "instructions/test_instruction_di.h"
#include "instructions/test_instruction_ei.h"
#include "instructions/test_instruction_hlt.h"
#include "instructions/test_instruction_in.h"
#include "instructions/test_instruction_inr_a.h"
#include "instructions/test_instruction_inr_b.h"
#include "instructions/test_instruction_inr_c.h"
#include "instructions/test_instruction_inr_d.h"
#include "instructions/test_instruction_inr_e.h"
#include "instructions/test_instruction_inr_h.h"
#include "instructions/test_instruction_inr_l.h"
#include "instructions/test_instruction_inr_m.h"
#include "instructions/test_instruction_inx_b.h"
#include "instructions/test_instruction_inx_d.h"
#include "instructions/test_instruction_inx_h.h"
#include "instructions/test_instruction_inx_sp.h"
#include "instructions/test_instruction_jc_adr.h"
#include "instructions/test_instruction_jm_adr.h"
#include "instructions/test_instruction_jmp_adr.h"
#include "instructions/test_instruction_jnc_adr.h"
#include "instructions/test_instruction_jnz_adr.h"
#include "instructions/test_instruction_jp_adr.h"
#include "instructions/test_instruction_jpe_adr.h"
#include "instructions/test_instruction_jpo_adr.h"
#include "instructions/test_instruction_jz_adr.h"
#include "instructions/test_instruction_lda_adr.h"
#include "instructions/test_instruction_ldax_b.h"
#include "instructions/test_instruction_ldax_d.h"
#include "instructions/test_instruction_lhld_adr.h"
#include "instructions/test_instruction_lxi_b.h"
#include "instructions/test_instruction_lxi_d.h"
#include "instructions/test_instruction_lxi_h.h"
#include "instructions/test_instruction_lxi_sp.h"
#include "instructions/test_instruction_mov_a_a.h"
#include "instructions/test_instruction_mov_a_b.h"
#include "instructions/test_instruction_mov_a_c.h"
#include "instructions/test_instruction_mov_a_d.h"
#include "instructions/test_instruction_mov_a_e.h"
#include "instructions/test_instruction_mov_a_h.h"
#include "instructions/test_instruction_mov_a_l.h"
#include "instructions/test_instruction_mov_a_m.h"
#include "instructions/test_instruction_mov_b_a.h"
#include "instructions/test_instruction_mov_b_b.h"
#include "instructions/test_instruction_mov_b_c.h"
#include "instructions/test_instruction_mov_b_d.h"
#include "instructions/test_instruction_mov_b_e.h"
#include "instructions/test_instruction_mov_b_h.h"
#include "instructions/test_instruction_mov_b_l.h"
#include "instructions/test_instruction_mov_b_m.h"
#include "instructions/test_instruction_mov_c_a.h"
#include "instructions/test_instruction_mov_c_b.h"
#include "instructions/test_instruction_mov_c_c.h"
#include "instructions/test_instruction_mov_c_d.h"
#include "instructions/test_instruction_mov_c_e.h"
#include "instructions/test_instruction_mov_c_h.h"
#include "instructions/test_instruction_mov_c_l.h"
#include "instructions/test_instruction_mov_c_m.h"
#include "instructions/test_instruction_mov_d_a.h"
#include "instructions/test_instruction_mov_d_b.h"
#include "instructions/test_instruction_mov_d_c.h"
#include "instructions/test_instruction_mov_d_d.h"
#include "instructions/test_instruction_mov_d_e.h"
#include "instructions/test_instruction_mov_d_h.h"
#include "instructions/test_instruction_mov_d_l.h"
#include "instructions/test_instruction_mov_d_m.h"
#include "instructions/test_instruction_mov_e_a.h"
#include "instructions/test_instruction_mov_e_b.h"
#include "instructions/test_instruction_mov_e_c.h"
#include "instructions/test_instruction_mov_e_d.h"
#include "instructions/test_instruction_mov_e_e.h"
#include "instructions/test_instruction_mov_e_h.h"
#include "instructions/test_instruction_mov_e_l.h"
#include "instructions/test_instruction_mov_e_m.h"
#include "instructions/test_instruction_mov_h_a.h"
#include "instructions/test_instruction_mov_h_b.h"
#include "instructions/test_instruction_mov_h_c.h"
#include "instructions/test_instruction_mov_h_d.h"
#include "instructions/test_instruction_mov_h_e.h"
#include "instructions/test_instruction_mov_h_h.h"
#include "instructions/test_instruction_mov_h_l.h"
#include "instructions/test_instruction_mov_h_m.h"
#include "instructions/test_instruction_mov_l_a.h"
#include "instructions/test_instruction_mov_l_b.h"
#include "instructions/test_instruction_mov_l_c.h"
#include "instructions/test_instruction_mov_l_d.h"
#include "instructions/test_instruction_mov_l_e.h"
#include "instructions/test_instruction_mov_l_h.h"
#include "instructions/test_instruction_mov_l_l.h"
#include "instructions/test_instruction_mov_l_m.h"
#include "instructions/test_instruction_mov_m_a.h"
#include "instructions/test_instruction_mov_m_b.h"
#include "instructions/test_instruction_mov_m_c.h"
#include "instructions/test_instruction_mov_m_d.h"
#include "instructions/test_instruction_mov_m_e.h"
#include "instructions/test_instruction_mov_m_h.h"
#include "instructions/test_instruction_mov_m_l.h"
#include "instructions/test_instruction_mvi_a.h"
#include "instructions/test_instruction_mvi_b.h"
#include "instructions/test_instruction_mvi_c.h"
#include "instructions/test_instruction_mvi_d.h"
#include "instructions/test_instruction_mvi_e.h"
#include "instructions/test_instruction_mvi_h.h"
#include "instructions/test_instruction_mvi_l.h"
#include "instructions/test_instruction_mvi_m.h"
#include "instructions/test_instruction_nop.h"
#include "instructions/test_instruction_ora_a.h"
#include "instructions/test_instruction_ora_b.h"
#include "instructions/test_instruction_ora_c.h"
#include "instructions/test_instruction_ora_d.h"
#include "instructions/test_instruction_ora_e.h"
#include "instructions/test_instruction_ora_h.h"
#include "instructions/test_instruction_ora_l.h"
#include "instructions/test_instruction_ora_m.h"
#include "instructions/test_instruction_ori.h"
#include "instructions/test_instruction_out.h"
#include "instructions/test_instruction_pchl.h"
#include "instructions/test_instruction_pop_b.h"
#include "instructions/test_instruction_pop_d.h"
#include "instructions/test_instruction_pop_h.h"
#include "instructions/test_instruction_pop_psw.h"
#include "instructions/test_instruction_push_b.h"
#include "instructions/test_instruction_push_d.h"
#include "instructions/test_instruction_push_h.h"
#include "instructions/test_instruction_push_psw.h"
#include "instructions/test_instruction_ral.h"
#include "instructions/test_instruction_rar.h"
#include "instructions/test_instruction_rc.h"
#include "instructions/test_instruction_ret.h"
#include "instructions/test_instruction_rim.h"
#include "instructions/test_instruction_rlc.h"
#include "instructions/test_instruction_rm.h"
#include "instructions/test_instruction_rnc.h"
#include "instructions/test_instruction_rnz.h"
#include "instructions/test_instruction_rp.h"
#include "instructions/test_instruction_rpe.h"
#include "instructions/test_instruction_rpo.h"
#include "instructions/test_instruction_rrc.h"
#include "instructions/test_instruction_rst_0.h"
#include "instructions/test_instruction_rst_1.h"
#include "instructions/test_instruction_rst_2.h"
#include "instructions/test_instruction_rst_3.h"
#include "instructions/test_instruction_rst_4.h"
#include "instructions/test_instruction_rst_5.h"
#include "instructions/test_instruction_rst_6.h"
#include "instructions/test_instruction_rst_7.h"
#include "instructions/test_instruction_rz.h"
#include "instructions/test_instruction_sbb_a.h"
#include "instructions/test_instruction_sbb_b.h"
#include "instructions/test_instruction_sbb_c.h"
#include "instructions/test_instruction_sbb_d.h"
#include "instructions/test_instruction_sbb_e.h"
#include "instructions/test_instruction_sbb_h.h"
#include "instructions/test_instruction_sbb_l.h"
#include "instructions/test_instruction_sbb_m.h"
#include "instructions/test_instruction_sbi.h"
#include "instructions/test_instruction_shld_adr.h"
#include "instructions/test_instruction_sim.h"
#include "instructions/test_instruction_sphl.h"
#include "instructions/test_instruction_sta_adr.h"
#include "instructions/test_instruction_stax_b.h"
#include "instructions/test_instruction_stax_d.h"
#include "instructions/test_instruction_stc.h"
#include "instructions/test_instruction_sub_a.h"
#include "instructions/test_instruction_sub_b.h"
#include "instructions/test_instruction_sub_c.h"
#include "instructions/test_instruction_sub_d.h"
#include "instructions/test_instruction_sub_e.h"
#include "instructions/test_instruction_sub_h.h"
#include "instructions/test_instruction_sub_l.h"
#include "instructions/test_instruction_sub_m.h"
#include "instructions/test_instruction_sui.h"
#include "instructions/test_instruction_xchg.h"
#include "instructions/test_instruction_xra_a.h"
#include "instructions/test_instruction_xra_b.h"
#include "instructions/test_instruction_xra_c.h"
#include "instructions/test_instruction_xra_d.h"
#include "instructions/test_instruction_xra_e.h"
#include "instructions/test_instruction_xra_h.h"
#include "instructions/test_instruction_xra_l.h"
#include "instructions/test_instruction_xra_m.h"
#include "instructions/test_instruction_xri.h"
#include "instructions/test_instruction_xthl.h"

#define NUM_TESTS (0xFF + 1)

typedef struct Harness {
	const char *name;
	uint8_t (*test)(uint8_t instr, BloomCPU* cpu);
	uint8_t result;
} Harness;

void initialize() {
}

Harness* make_test(uint8_t opcode, uint8_t (*test)(uint8_t instr, BloomCPU* cpu), const char* name) {
	Harness *h = malloc(sizeof(Harness));
	h->name = name;
	h->test = test;
	h->result = 0;

	return h;
}

int main(void) {

	initialize();

	struct Harness* tests[NUM_TESTS];

	tests[0x00] = make_test(0x00, test_instruction_nop, "nop");
	tests[0x01] = make_test(0x01, test_instruction_lxi_b, "lxi_b");
	tests[0x02] = make_test(0x02, test_instruction_stax_b, "stax_b");
	tests[0x03] = make_test(0x03, test_instruction_inx_b, "inx_b");
	tests[0x04] = make_test(0x04, test_instruction_inr_b, "inr_b");
	tests[0x05] = make_test(0x05, test_instruction_dcr_b, "dcr_b");
	tests[0x06] = make_test(0x06, test_instruction_mvi_b, "mvi_b");
	tests[0x07] = make_test(0x07, test_instruction_rlc, "rlc");
	tests[0x08] = NULL;
	tests[0x09] = make_test(0x09, test_instruction_dad_b, "dad_b");
	tests[0x0a] = make_test(0x0a, test_instruction_ldax_b, "ldax_b");
	tests[0x0b] = make_test(0x0b, test_instruction_dcx_b, "dcx_b");
	tests[0x0c] = make_test(0x0c, test_instruction_inr_c, "inr_c");
	tests[0x0d] = make_test(0x0d, test_instruction_dcr_c, "dcr_c");
	tests[0x0e] = make_test(0x0e, test_instruction_mvi_c, "mvi_c");
	tests[0x0f] = make_test(0x0f, test_instruction_rrc, "rrc");
	tests[0x10] = NULL;
	tests[0x11] = make_test(0x11, test_instruction_lxi_d, "lxi_d");
	tests[0x12] = make_test(0x12, test_instruction_stax_d, "stax_d");
	tests[0x13] = make_test(0x13, test_instruction_inx_d, "inx_d");
	tests[0x14] = make_test(0x14, test_instruction_inr_d, "inr_d");
	tests[0x15] = make_test(0x15, test_instruction_dcr_d, "dcr_d");
	tests[0x16] = make_test(0x16, test_instruction_mvi_d, "mvi_d");
	tests[0x17] = make_test(0x17, test_instruction_ral, "ral");
	tests[0x18] = NULL;
	tests[0x19] = make_test(0x19, test_instruction_dad_d, "dad_d");
	tests[0x1a] = make_test(0x1a, test_instruction_ldax_d, "ldax_d");
	tests[0x1b] = make_test(0x1b, test_instruction_dcx_d, "dcx_d");
	tests[0x1c] = make_test(0x1c, test_instruction_inr_e, "inr_e");
	tests[0x1d] = make_test(0x1d, test_instruction_dcr_e, "dcr_e");
	tests[0x1e] = make_test(0x1e, test_instruction_mvi_e, "mvi_e");
	tests[0x1f] = make_test(0x1f, test_instruction_rar, "rar");
	tests[0x20] = make_test(0x20, test_instruction_rim, "rim");
	tests[0x21] = make_test(0x21, test_instruction_lxi_h, "lxi_h");
	tests[0x22] = make_test(0x22, test_instruction_shld_adr, "shld_adr");
	tests[0x23] = make_test(0x23, test_instruction_inx_h, "inx_h");
	tests[0x24] = make_test(0x24, test_instruction_inr_h, "inr_h");
	tests[0x25] = make_test(0x25, test_instruction_dcr_h, "dcr_h");
	tests[0x26] = make_test(0x26, test_instruction_mvi_h, "mvi_h");
	tests[0x27] = make_test(0x27, test_instruction_daa, "daa");
	tests[0x28] = NULL;
	tests[0x29] = make_test(0x29, test_instruction_dad_h, "dad_h");
	tests[0x2a] = make_test(0x2a, test_instruction_lhld_adr, "lhld_adr");
	tests[0x2b] = make_test(0x2b, test_instruction_dcx_h, "dcx_h");
	tests[0x2c] = make_test(0x2c, test_instruction_inr_l, "inr_l");
	tests[0x2d] = make_test(0x2d, test_instruction_dcr_l, "dcr_l");
	tests[0x2e] = make_test(0x2e, test_instruction_mvi_l, "mvi_l");
	tests[0x2f] = make_test(0x2f, test_instruction_cma, "cma");
	tests[0x30] = make_test(0x30, test_instruction_sim, "sim");
	tests[0x31] = make_test(0x31, test_instruction_lxi_sp, "lxi_sp");
	tests[0x32] = make_test(0x32, test_instruction_sta_adr, "sta_adr");
	tests[0x33] = make_test(0x33, test_instruction_inx_sp, "inx_sp");
	tests[0x34] = make_test(0x34, test_instruction_inr_m, "inr_m");
	tests[0x35] = make_test(0x35, test_instruction_dcr_m, "dcr_m");
	tests[0x36] = make_test(0x36, test_instruction_mvi_m, "mvi_m");
	tests[0x37] = make_test(0x37, test_instruction_stc, "stc");
	tests[0x38] = NULL;
	tests[0x39] = make_test(0x39, test_instruction_dad_sp, "dad_sp");
	tests[0x3a] = make_test(0x3a, test_instruction_lda_adr, "lda_adr");
	tests[0x3b] = make_test(0x3b, test_instruction_dcx_sp, "dcx_sp");
	tests[0x3c] = make_test(0x3c, test_instruction_inr_a, "inr_a");
	tests[0x3d] = make_test(0x3d, test_instruction_dcr_a, "dcr_a");
	tests[0x3e] = make_test(0x3e, test_instruction_mvi_a, "mvi_a");
	tests[0x3f] = make_test(0x3f, test_instruction_cmc, "cmc");
	tests[0x40] = make_test(0x40, test_instruction_mov_b_b, "mov_b_b");
	tests[0x41] = make_test(0x41, test_instruction_mov_b_c, "mov_b_c");
	tests[0x42] = make_test(0x42, test_instruction_mov_b_d, "mov_b_d");
	tests[0x43] = make_test(0x43, test_instruction_mov_b_e, "mov_b_e");
	tests[0x44] = make_test(0x44, test_instruction_mov_b_h, "mov_b_h");
	tests[0x45] = make_test(0x45, test_instruction_mov_b_l, "mov_b_l");
	tests[0x46] = make_test(0x46, test_instruction_mov_b_m, "mov_b_m");
	tests[0x47] = make_test(0x47, test_instruction_mov_b_a, "mov_b_a");
	tests[0x48] = make_test(0x48, test_instruction_mov_c_b, "mov_c_b");
	tests[0x49] = make_test(0x49, test_instruction_mov_c_c, "mov_c_c");
	tests[0x4a] = make_test(0x4a, test_instruction_mov_c_d, "mov_c_d");
	tests[0x4b] = make_test(0x4b, test_instruction_mov_c_e, "mov_c_e");
	tests[0x4c] = make_test(0x4c, test_instruction_mov_c_h, "mov_c_h");
	tests[0x4d] = make_test(0x4d, test_instruction_mov_c_l, "mov_c_l");
	tests[0x4e] = make_test(0x4e, test_instruction_mov_c_m, "mov_c_m");
	tests[0x4f] = make_test(0x4f, test_instruction_mov_c_a, "mov_c_a");
	tests[0x50] = make_test(0x50, test_instruction_mov_d_b, "mov_d_b");
	tests[0x51] = make_test(0x51, test_instruction_mov_d_c, "mov_d_c");
	tests[0x52] = make_test(0x52, test_instruction_mov_d_d, "mov_d_d");
	tests[0x53] = make_test(0x53, test_instruction_mov_d_e, "mov_d_e");
	tests[0x54] = make_test(0x54, test_instruction_mov_d_h, "mov_d_h");
	tests[0x55] = make_test(0x55, test_instruction_mov_d_l, "mov_d_l");
	tests[0x56] = make_test(0x56, test_instruction_mov_d_m, "mov_d_m");
	tests[0x57] = make_test(0x57, test_instruction_mov_d_a, "mov_d_a");
	tests[0x58] = make_test(0x58, test_instruction_mov_e_b, "mov_e_b");
	tests[0x59] = make_test(0x59, test_instruction_mov_e_c, "mov_e_c");
	tests[0x5a] = make_test(0x5a, test_instruction_mov_e_d, "mov_e_d");
	tests[0x5b] = make_test(0x5b, test_instruction_mov_e_e, "mov_e_e");
	tests[0x5c] = make_test(0x5c, test_instruction_mov_e_h, "mov_e_h");
	tests[0x5d] = make_test(0x5d, test_instruction_mov_e_l, "mov_e_l");
	tests[0x5e] = make_test(0x5e, test_instruction_mov_e_m, "mov_e_m");
	tests[0x5f] = make_test(0x5f, test_instruction_mov_e_a, "mov_e_a");
	tests[0x60] = make_test(0x60, test_instruction_mov_h_b, "mov_h_b");
	tests[0x61] = make_test(0x61, test_instruction_mov_h_c, "mov_h_c");
	tests[0x62] = make_test(0x62, test_instruction_mov_h_d, "mov_h_d");
	tests[0x63] = make_test(0x63, test_instruction_mov_h_e, "mov_h_e");
	tests[0x64] = make_test(0x64, test_instruction_mov_h_h, "mov_h_h");
	tests[0x65] = make_test(0x65, test_instruction_mov_h_l, "mov_h_l");
	tests[0x66] = make_test(0x66, test_instruction_mov_h_m, "mov_h_m");
	tests[0x67] = make_test(0x67, test_instruction_mov_h_a, "mov_h_a");
	tests[0x68] = make_test(0x68, test_instruction_mov_l_b, "mov_l_b");
	tests[0x69] = make_test(0x69, test_instruction_mov_l_c, "mov_l_c");
	tests[0x6a] = make_test(0x6a, test_instruction_mov_l_d, "mov_l_d");
	tests[0x6b] = make_test(0x6b, test_instruction_mov_l_e, "mov_l_e");
	tests[0x6c] = make_test(0x6c, test_instruction_mov_l_h, "mov_l_h");
	tests[0x6d] = make_test(0x6d, test_instruction_mov_l_l, "mov_l_l");
	tests[0x6e] = make_test(0x6e, test_instruction_mov_l_m, "mov_l_m");
	tests[0x6f] = make_test(0x6f, test_instruction_mov_l_a, "mov_l_a");
	tests[0x70] = make_test(0x70, test_instruction_mov_m_b, "mov_m_b");
	tests[0x71] = make_test(0x71, test_instruction_mov_m_c, "mov_m_c");
	tests[0x72] = make_test(0x72, test_instruction_mov_m_d, "mov_m_d");
	tests[0x73] = make_test(0x73, test_instruction_mov_m_e, "mov_m_e");
	tests[0x74] = make_test(0x74, test_instruction_mov_m_h, "mov_m_h");
	tests[0x75] = make_test(0x75, test_instruction_mov_m_l, "mov_m_l");
	tests[0x76] = make_test(0x76, test_instruction_hlt, "hlt");
	tests[0x77] = make_test(0x77, test_instruction_mov_m_a, "mov_m_a");
	tests[0x78] = make_test(0x78, test_instruction_mov_a_b, "mov_a_b");
	tests[0x79] = make_test(0x79, test_instruction_mov_a_c, "mov_a_c");
	tests[0x7a] = make_test(0x7a, test_instruction_mov_a_d, "mov_a_d");
	tests[0x7b] = make_test(0x7b, test_instruction_mov_a_e, "mov_a_e");
	tests[0x7c] = make_test(0x7c, test_instruction_mov_a_h, "mov_a_h");
	tests[0x7d] = make_test(0x7d, test_instruction_mov_a_l, "mov_a_l");
	tests[0x7e] = make_test(0x7e, test_instruction_mov_a_m, "mov_a_m");
	tests[0x7f] = make_test(0x7f, test_instruction_mov_a_a, "mov_a_a");
	tests[0x80] = make_test(0x80, test_instruction_add_b, "add_b");
	tests[0x81] = make_test(0x81, test_instruction_add_c, "add_c");
	tests[0x82] = make_test(0x82, test_instruction_add_d, "add_d");
	tests[0x83] = make_test(0x83, test_instruction_add_e, "add_e");
	tests[0x84] = make_test(0x84, test_instruction_add_h, "add_h");
	tests[0x85] = make_test(0x85, test_instruction_add_l, "add_l");
	tests[0x86] = make_test(0x86, test_instruction_add_m, "add_m");
	tests[0x87] = make_test(0x87, test_instruction_add_a, "add_a");
	tests[0x88] = make_test(0x88, test_instruction_adc_b, "adc_b");
	tests[0x89] = make_test(0x89, test_instruction_adc_c, "adc_c");
	tests[0x8a] = make_test(0x8a, test_instruction_adc_d, "adc_d");
	tests[0x8b] = make_test(0x8b, test_instruction_adc_e, "adc_e");
	tests[0x8c] = make_test(0x8c, test_instruction_adc_h, "adc_h");
	tests[0x8d] = make_test(0x8d, test_instruction_adc_l, "adc_l");
	tests[0x8e] = make_test(0x8e, test_instruction_adc_m, "adc_m");
	tests[0x8f] = make_test(0x8f, test_instruction_adc_a, "adc_a");
	tests[0x90] = make_test(0x90, test_instruction_sub_b, "sub_b");
	tests[0x91] = make_test(0x91, test_instruction_sub_c, "sub_c");
	tests[0x92] = make_test(0x92, test_instruction_sub_d, "sub_d");
	tests[0x93] = make_test(0x93, test_instruction_sub_e, "sub_e");
	tests[0x94] = make_test(0x94, test_instruction_sub_h, "sub_h");
	tests[0x95] = make_test(0x95, test_instruction_sub_l, "sub_l");
	tests[0x96] = make_test(0x96, test_instruction_sub_m, "sub_m");
	tests[0x97] = make_test(0x97, test_instruction_sub_a, "sub_a");
	tests[0x98] = make_test(0x98, test_instruction_sbb_b, "sbb_b");
	tests[0x99] = make_test(0x99, test_instruction_sbb_c, "sbb_c");
	tests[0x9a] = make_test(0x9a, test_instruction_sbb_d, "sbb_d");
	tests[0x9b] = make_test(0x9b, test_instruction_sbb_e, "sbb_e");
	tests[0x9c] = make_test(0x9c, test_instruction_sbb_h, "sbb_h");
	tests[0x9d] = make_test(0x9d, test_instruction_sbb_l, "sbb_l");
	tests[0x9e] = make_test(0x9e, test_instruction_sbb_m, "sbb_m");
	tests[0x9f] = make_test(0x9f, test_instruction_sbb_a, "sbb_a");
	tests[0xa0] = make_test(0xa0, test_instruction_ana_b, "ana_b");
	tests[0xa1] = make_test(0xa1, test_instruction_ana_c, "ana_c");
	tests[0xa2] = make_test(0xa2, test_instruction_ana_d, "ana_d");
	tests[0xa3] = make_test(0xa3, test_instruction_ana_e, "ana_e");
	tests[0xa4] = make_test(0xa4, test_instruction_ana_h, "ana_h");
	tests[0xa5] = make_test(0xa5, test_instruction_ana_l, "ana_l");
	tests[0xa6] = make_test(0xa6, test_instruction_ana_m, "ana_m");
	tests[0xa7] = make_test(0xa7, test_instruction_ana_a, "ana_a");
	tests[0xa8] = make_test(0xa8, test_instruction_xra_b, "xra_b");
	tests[0xa9] = make_test(0xa9, test_instruction_xra_c, "xra_c");
	tests[0xaa] = make_test(0xaa, test_instruction_xra_d, "xra_d");
	tests[0xab] = make_test(0xab, test_instruction_xra_e, "xra_e");
	tests[0xac] = make_test(0xac, test_instruction_xra_h, "xra_h");
	tests[0xad] = make_test(0xad, test_instruction_xra_l, "xra_l");
	tests[0xae] = make_test(0xae, test_instruction_xra_m, "xra_m");
	tests[0xaf] = make_test(0xaf, test_instruction_xra_a, "xra_a");
	tests[0xb0] = make_test(0xb0, test_instruction_ora_b, "ora_b");
	tests[0xb1] = make_test(0xb1, test_instruction_ora_c, "ora_c");
	tests[0xb2] = make_test(0xb2, test_instruction_ora_d, "ora_d");
	tests[0xb3] = make_test(0xb3, test_instruction_ora_e, "ora_e");
	tests[0xb4] = make_test(0xb4, test_instruction_ora_h, "ora_h");
	tests[0xb5] = make_test(0xb5, test_instruction_ora_l, "ora_l");
	tests[0xb6] = make_test(0xb6, test_instruction_ora_m, "ora_m");
	tests[0xb7] = make_test(0xb7, test_instruction_ora_a, "ora_a");
	tests[0xb8] = make_test(0xb8, test_instruction_cmp_b, "cmp_b");
	tests[0xb9] = make_test(0xb9, test_instruction_cmp_c, "cmp_c");
	tests[0xba] = make_test(0xba, test_instruction_cmp_d, "cmp_d");
	tests[0xbb] = make_test(0xbb, test_instruction_cmp_e, "cmp_e");
	tests[0xbc] = make_test(0xbc, test_instruction_cmp_h, "cmp_h");
	tests[0xbd] = make_test(0xbd, test_instruction_cmp_l, "cmp_l");
	tests[0xbe] = make_test(0xbe, test_instruction_cmp_m, "cmp_m");
	tests[0xbf] = make_test(0xbf, test_instruction_cmp_a, "cmp_a");
	tests[0xc0] = make_test(0xc0, test_instruction_rnz, "rnz");
	tests[0xc1] = make_test(0xc1, test_instruction_pop_b, "pop_b");
	tests[0xc2] = make_test(0xc2, test_instruction_jnz_adr, "jnz_adr");
	tests[0xc3] = make_test(0xc3, test_instruction_jmp_adr, "jmp_adr");
	tests[0xc4] = make_test(0xc4, test_instruction_cnz_adr, "cnz_adr");
	tests[0xc5] = make_test(0xc5, test_instruction_push_b, "push_b");
	tests[0xc6] = make_test(0xc6, test_instruction_adi, "adi");
	tests[0xc7] = make_test(0xc7, test_instruction_rst_0, "rst_0");
	tests[0xc8] = make_test(0xc8, test_instruction_rz, "rz");
	tests[0xc9] = make_test(0xc9, test_instruction_ret, "ret");
	tests[0xca] = make_test(0xca, test_instruction_jz_adr, "jz_adr");
	tests[0xcb] = NULL;
	tests[0xcc] = make_test(0xcc, test_instruction_cz_adr, "cz_adr");
	tests[0xcd] = make_test(0xcd, test_instruction_call_adr, "call_adr");
	tests[0xce] = make_test(0xce, test_instruction_aci, "aci");
	tests[0xcf] = make_test(0xcf, test_instruction_rst_1, "rst_1");
	tests[0xd0] = make_test(0xd0, test_instruction_rnc, "rnc");
	tests[0xd1] = make_test(0xd1, test_instruction_pop_d, "pop_d");
	tests[0xd2] = make_test(0xd2, test_instruction_jnc_adr, "jnc_adr");
	tests[0xd3] = make_test(0xd3, test_instruction_out, "out");
	tests[0xd4] = make_test(0xd4, test_instruction_cnc_adr, "cnc_adr");
	tests[0xd5] = make_test(0xd5, test_instruction_push_d, "push_d");
	tests[0xd6] = make_test(0xd6, test_instruction_sui, "sui");
	tests[0xd7] = make_test(0xd7, test_instruction_rst_2, "rst_2");
	tests[0xd8] = make_test(0xd8, test_instruction_rc, "rc");
	tests[0xd9] = NULL;
	tests[0xda] = make_test(0xda, test_instruction_jc_adr, "jc_adr");
	tests[0xdb] = make_test(0xdb, test_instruction_in, "in");
	tests[0xdc] = make_test(0xdc, test_instruction_cc_adr, "cc_adr");
	tests[0xdd] = NULL;
	tests[0xde] = make_test(0xde, test_instruction_sbi, "sbi");
	tests[0xdf] = make_test(0xdf, test_instruction_rst_3, "rst_3");
	tests[0xe0] = make_test(0xe0, test_instruction_rpo, "rpo");
	tests[0xe1] = make_test(0xe1, test_instruction_pop_h, "pop_h");
	tests[0xe2] = make_test(0xe2, test_instruction_jpo_adr, "jpo_adr");
	tests[0xe3] = make_test(0xe3, test_instruction_xthl, "xthl");
	tests[0xe4] = make_test(0xe4, test_instruction_cpo_adr, "cpo_adr");
	tests[0xe5] = make_test(0xe5, test_instruction_push_h, "push_h");
	tests[0xe6] = make_test(0xe6, test_instruction_ani, "ani");
	tests[0xe7] = make_test(0xe7, test_instruction_rst_4, "rst_4");
	tests[0xe8] = make_test(0xe8, test_instruction_rpe, "rpe");
	tests[0xe9] = make_test(0xe9, test_instruction_pchl, "pchl");
	tests[0xea] = make_test(0xea, test_instruction_jpe_adr, "jpe_adr");
	tests[0xeb] = make_test(0xeb, test_instruction_xchg, "xchg");
	tests[0xec] = make_test(0xec, test_instruction_cpe_adr, "cpe_adr");
	tests[0xed] = NULL;
	tests[0xee] = make_test(0xee, test_instruction_xri, "xri");
	tests[0xef] = make_test(0xef, test_instruction_rst_5, "rst_5");
	tests[0xf0] = make_test(0xf0, test_instruction_rp, "rp");
	tests[0xf1] = make_test(0xf1, test_instruction_pop_psw, "pop_psw");
	tests[0xf2] = make_test(0xf2, test_instruction_jp_adr, "jp_adr");
	tests[0xf3] = make_test(0xf3, test_instruction_di, "di");
	tests[0xf4] = make_test(0xf4, test_instruction_cp_adr, "cp_adr");
	tests[0xf5] = make_test(0xf5, test_instruction_push_psw, "push_psw");
	tests[0xf6] = make_test(0xf6, test_instruction_ori, "ori");
	tests[0xf7] = make_test(0xf7, test_instruction_rst_6, "rst_6");
	tests[0xf8] = make_test(0xf8, test_instruction_rm, "rm");
	tests[0xf9] = make_test(0xf9, test_instruction_sphl, "sphl");
	tests[0xfa] = make_test(0xfa, test_instruction_jm_adr, "jm_adr");
	tests[0xfb] = make_test(0xfb, test_instruction_ei, "ei");
	tests[0xfc] = make_test(0xfc, test_instruction_cm_adr, "cm_adr");
	tests[0xfd] = NULL;
	tests[0xfe] = make_test(0xfe, test_instruction_cpi, "cpi");
	tests[0xff] = make_test(0xff, test_instruction_rst_7, "rst_7");

	uint16_t failures = 0;
	uint16_t passed = 0;
	for (uint16_t i = 0; i < NUM_TESTS; i++) {
		if (tests[i] != NULL) {
			BloomCPU *cpu = cpu_create();
			tests[i]->result = tests[i]->test(i, cpu);
			cpu_destroy(cpu);
			
			if (tests[i]->result != 0) {
				fprintf(stderr, "\033[0;31m[FAILED] ");
				failures++;
			} else {
				fprintf(stderr, "\033[0;32m[PASSED] ");
				passed++;
			}
			fprintf(stderr, "\033[0m");
			fprintf(stderr, "Running test 0x%02X ('test_instruction_%s')\n", i, tests[i]->name);
		}
	}

	if (failures > 0) {
		fprintf(stderr, "\033[0;31m");
	} else {
		fprintf(stderr, "\033[0;32m");
	}
	fprintf(stderr, "\n[%i / %i] Tests Passed (%i Failed)\n", passed, passed + failures, failures);
	fprintf(stderr, "\033[0m");

	return (failures > 0);
}

