#include <stdio.h>
#include <mips.h>

void mux(Signal in1, Signal in2, Signal ctl, Signal *out1)
{
    /* Exercise 6-1 */
}

void mux4(Signal in1, Signal in2, Signal in3, Signal in4, Signal ctl1, Signal ctl2, Signal *out1)
{
    Signal inner1[3], inner2[3], inner3[3], inner4[3], inner5[4];

    /* ctl1 != true && ctl2 != true) */
    not_gate(ctl1, inner1 + 0);
    not_gate(ctl2, inner1 + 1);
    inner1[2] = in1;
    andn_gate(inner1, 3, inner5 + 0);
    /* ctl1 == true && ctl2 != true) */
    inner2[0] = ctl1;
    not_gate(ctl2, inner2 + 1);
    inner2[2] = in2;
    andn_gate(inner2, 3, inner5 + 1);
    /* (ctl1 != true && ctl2 == true) */
    not_gate(ctl1, inner3 + 0);
    inner3[1] = ctl2;
    inner3[2] = in3;
    andn_gate(inner3, 3, inner5 + 2);
    /* (ctl1 == true && ctl2 == true) */
    inner4[0] = ctl1;
    inner4[1] = ctl2;
    inner4[2] = in4;
    andn_gate(inner4, 3, inner5 + 3);
    
    orn_gate(inner5, 4, out1);
}

void alu(Signal *ops, Signal a, Signal b, Signal less, Signal carry_in, Signal *s, Signal *carry_out)
{
    /* Exercise 6-1 */
}

void alu_msb(Signal *ops, Signal a, Signal b, Signal less, Signal carry_in, Signal *s, Signal *carry_out, Signal *set)
{
    /* Exercise 6-1 */
}

void alu32(Signal *ops, Word a, Word b, Word *s, Signal *zero)
{
    /* Exercise 6-1 */
}

void test_alu()
{
    /* Exercise 6-1 */
    Signal a, b, carry_in, s, carry_out;
    Signal ops[3];
    
    /* AND */
    ops[0] = false;
    ops[1] = false;
    ops[2] = false;
    for (carry_in = 0; carry_in <= 1; ++carry_in) {
        for (a = 0; a <= 1; ++a) {
            for (b = 0; b <= 1; ++b) {
                alu(ops, a, b, false, carry_in, &s, &carry_out);
                printf("ALU(AND, %d, %d, %d) => (%d, %d)\n", a, b, carry_in, s, carry_out);
            }
        }
    }
    /* OR */
    /* ADD */
}

void test_alu32(int val1, int val2)
{
    /* Exercise 6-1 */
    Signal ops[3];
    Word in1, in2, out1;
    Signal carry_in, carry_out;
    word_set_value(&in1, val1);
    word_set_value(&in2, val2);
    carry_in = false;
    
    /* AND */
    ops[0] = false;
    ops[1] = false;
    ops[2] = false;
    alu32(ops, in1, in2, &out1, &carry_out);
    printf("ALU32(AND, %x, %x, %d) => (%x, %d)\n", val1, val2, carry_in, word_get_value(out1), carry_out);

    /* OR */
    /* ADD */
    /* SUB (also check zero?) */
    /* SLT */

}
