#include <mips.h>

int main()
{
    /* Exercise 5-1 */
    // test_gate();

    /* Exercise 5-2 */
    // test_full_adder();

    /* Exercise 5-3 */
    // test_rca(-200, 200);
    // test_rca(0, 1);
    // test_rca(8, 16);
    // test_rca(100, -68);
    // test_rca(-1, 0);

    /* Exercise 6-1 */
    // test_alu();
    // test_alu32(100, 200);
    // test_alu32(1, 0);
    // test_alu32(__INT32_MAX__-20000, 30000);
    // test_alu32(__INT32_MAX__-20000, -30000);
    // test_alu32(-(__INT32_MAX__-20000), 30000);
    // test_alu32(-(__INT32_MAX__-20000), -30000);
    // printf("%d\n", -(__INT32_MAX__-20000) < 30000); 1だった
    /* Exercise 7-1 */
    test_register_file();

    /* Exercise 7-2 */
    /* test_inst_memory(); */
    /* test_data_memory(); */

    /* Exercise 8-1 */
    /* test_mips(); */

    return 0;
}
