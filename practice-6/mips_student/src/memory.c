#include <stdio.h>
#include <mips.h>

void inst_memory_run(InstMemory *im, Word addr, Word *inst)
{
    /* Exercise 7-2 */
}

void inst_memory_set_inst(InstMemory *im, int addr, int inst)
{
    /* Exercise 7-2 */
}

void data_memory_run(DataMemory *dm, Signal mem_write, Signal mem_read, Word addr, Word wdata, Word *rdata)
{
    /* Exercise 7-2 */
    int val, offset;
    val = word_get_value(addr);
    offset = (val - DATA_MEM_START) / 4;
    
    if (mem_read) {
        /* ... */
    }
    else if (mem_write) {
        /* ... */
    }
}

void test_inst_memory()
{
    Word addr, inst;
    InstMemory im;

    word_set_value(&addr, 0x04000000);
    inst_memory_set_inst(&im, 0x04000000, 350);
    inst_memory_run(&im, addr, &inst);

    printf("InstMemory[0x04000000] = %d\n", word_get_value(inst));

}

void test_data_memory()
{
    DataMemory dm;
    Signal mem_write, mem_read;
    Word addr, wdata, rdata;
    
    word_set_value(&rdata, 0);
    mem_write = true;
    mem_read = false;

    word_set_value(&addr, 0x10000004);
    word_set_value(&wdata, 100);
    data_memory_run(&dm, mem_write, mem_read, addr, wdata, &rdata);

    word_set_value(&addr, 0x10000008);
    word_set_value(&wdata, 200);
    data_memory_run(&dm, mem_write, mem_read, addr, wdata, &rdata);

    printf("rdata : %d\n", word_get_value(rdata));

    mem_write = false;
    mem_read = true;
    data_memory_run(&dm, mem_write, mem_read, addr, wdata, &rdata);
    printf("rdata : %d\n", word_get_value(rdata));

    word_set_value(&addr, 0x10000004);
    data_memory_run(&dm, mem_write, mem_read, addr, wdata, &rdata);
    printf("rdata : %d\n", word_get_value(rdata));

}


