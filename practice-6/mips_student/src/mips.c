#include <stdio.h>
#include <mips.h>

void mips_run(MIPS *m, int inst_num)
{
    Word npaddr, paddr;
    Word instr;
    Word wdata, rdata1, rdata2;
    Signal register_dst, register_write, alu_op1, ops[3];
    Signal zero, zero4;
    int i;
    for (i = 0; i < inst_num; ++i) {
        /* Exercise 8-1 */
        /* ... */

        Signal pcadd[3] = {false, true, false};
        Word four;
        word_set_value(&four, 4);
        alu32(pcadd, paddr, four, &npaddr, &zero4);
        register_run(&(m->pc), true, npaddr, &paddr);
        printf("$t0 = %x\n", register_get_value(m->rf.r + 8));
    }
}

void mips_init(MIPS *m, int inst[], int inst_num)
{
    int i;
    register_set_value(&(m->pc), INST_MEM_START);
    register_set_value((m->rf.r + 9), 0x100);
    register_set_value((m->rf.r + 10), 0x300);
    for (i = 0; i < inst_num; ++i) {
        inst_memory_set_inst(&(m->im), INST_MEM_START + 4 * i, inst[i]);
    }
}

void test_mips()
{
    MIPS m;
    int inst[] = {0x012a4020,
                  0x012a4022,
                  0x012a4024,
                  0x012a4025,
                  0x012a402a};
    mips_init(&m, inst, 5);
    mips_run(&m, 5);
    
}
