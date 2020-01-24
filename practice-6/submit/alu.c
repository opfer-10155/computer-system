#include <stdio.h>
#include <mips.h>

void mux(Signal in1, Signal in2, Signal ctl, Signal *out1)
{
    /* Exercise 6-1 */
    Signal inner1, inner2;
    not_gate(ctl, &inner1);
    and_gate(in1, inner1, &inner1);
    and_gate(in2, ctl, &inner2);
    or_gate(inner1, inner2, out1);
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
    Signal inner0, inner1, inner2, inner3;
    not_gate(b, &inner0);
    mux(b, inner0, ops[2], &inner0);

    and_gate(a, b, &inner1);
    or_gate(a, b, &inner2);
    full_adder(a, inner0, carry_in, &inner3, carry_out);
    mux4(inner1, inner2, inner3, less, ops[0], ops[1], s);

}

void alu_msb(Signal *ops, Signal a, Signal b, Signal less, Signal carry_in, Signal *s, Signal *carry_out, Signal *set, Signal *overflow)
{
    /* Exercise 6-1 */
    Signal inner0, inner1, inner2, inner3;

    // check binvert
    not_gate(b, &inner0);
    mux(b, inner0, ops[2], &inner0);

    and_gate(a, b, &inner1);
    or_gate(a, b, &inner2);
    full_adder(a, inner0, carry_in, &inner3, carry_out);

    // check overflow
    // overflow = (!bv * !a * !b * s) + (!bv * a * b * !s) + (bv * !a * b * s) + (bv * a * !b * !s)
    Signal inner4, inner5, inner6, inner7, not_a, not_b, not_bv, not_sum;
    Signal sum = inner3;
    Signal bv = ops[2];
    not_gate(a, &not_a);
    not_gate(b, &not_b);
    not_gate(ops[2], &not_bv);
    not_gate(inner3, &not_sum);
    Signal tmp1[4] = { not_bv, not_a, not_b, sum };
    Signal tmp2[4] = { not_bv, a, b, not_sum };
    Signal tmp3[4] = { bv, not_a, b, sum };
    Signal tmp4[4] = { bv, a, not_b, not_sum };
    andn_gate(tmp1, 4, &inner4);
    andn_gate(tmp2, 4, &inner5);
    andn_gate(tmp3, 4, &inner6);
    andn_gate(tmp4, 4, &inner7);
    Signal tmp[4] = { inner4, inner5, inner6, inner7 };
    orn_gate(tmp, 4, overflow);

    *set = inner3;
    mux4(inner1, inner2, inner3, less, ops[0], ops[1], s);
}

void alu32(Signal *ops, Word a, Word b, Word *s, Signal *zero, Signal *overflow)
{
    /* Exercise 6-1 */
    Signal carry_in, carry_out, set;
    carry_in = ops[2];
    for(int i=0; i<31; i++) {
        alu(ops, a.bit[i], b.bit[i], false, carry_in, s->bit+i, &carry_out);
        carry_in = carry_out;
    }

    alu_msb(ops, a.bit[31], b.bit[31], false, carry_in, s->bit+31, &carry_out, &set, overflow);
    alu(ops, a.bit[0], b.bit[0], set, ops[2], s->bit, &carry_out);

    orn_gate(s->bit, 32, zero);
    not_gate(*zero, zero);
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
    ops[0] = true;
    ops[1] = false;
    ops[2] = false;
    for (carry_in = 0; carry_in <= 1; ++carry_in) {
        for (a = 0; a <= 1; ++a) {
            for (b = 0; b <= 1; ++b) {
                alu(ops, a, b, false, carry_in, &s, &carry_out);
                printf("ALU(OR, %d, %d, %d) => (%d, %d)\n", a, b, carry_in, s, carry_out);
            }
        }
    }

    /* ADD */
    ops[0] = false;
    ops[1] = true;
    ops[2] = false;
    for (carry_in = 0; carry_in <= 1; ++carry_in) {
        for (a = 0; a <= 1; ++a) {
            for (b = 0; b <= 1; ++b) {
                alu(ops, a, b, false, carry_in, &s, &carry_out);
                printf("ALU(ADD, %d, %d, %d) => (%d, %d)\n", a, b, carry_in, s, carry_out);
            }
        }
    }
}

void test_alu32(int val1, int val2)
{
    /* Exercise 6-1 */
    Signal ops[3];
    Word in1, in2, out1;
    Signal carry_in, carry_out, zero, overflow;
    word_set_value(&in1, val1);
    word_set_value(&in2, val2);
    // carry_in = false;

    /* AND */
    ops[0] = false;
    ops[1] = false;
    ops[2] = false;
    carry_in = ops[2];
    alu32(ops, in1, in2, &out1, &carry_out, &overflow);
    printf("ALU32(AND, %d, %d) => %d\n", val1, val2, word_get_value(out1));
    printf("val1 = "); word_print(in1); puts("");
    printf("val2 = "); word_print(in2); puts("");
    printf("ans  = "); word_print(out1); puts("");

    /* OR */
    ops[0] = true;
    ops[1] = false;
    ops[2] = false;
    carry_in = ops[2];
    alu32(ops, in1, in2, &out1, &carry_out, &overflow);
    printf("ALU32(OR, %d, %d) => %d\n", val1, val2, word_get_value(out1));
    printf("val1 = "); word_print(in1); puts("");
    printf("val2 = "); word_print(in2); puts("");
    printf("ans  = "); word_print(out1); puts("");

    /* ADD */
    ops[0] = false;
    ops[1] = true;
    ops[2] = false;
    carry_in = ops[2];
    alu32(ops, in1, in2, &out1, &carry_out, &overflow);
    printf("ALU32(ADD, %d, %d) => (%d, %d)\n", val1, val2, word_get_value(out1), overflow);
    printf("val1 = "); word_print(in1); puts("");
    printf("val2 = "); word_print(in2); puts("");
    printf("ans  = "); word_print(out1); puts("");
    printf("check overflow %d\n", overflow);

    /* SUB (also check zero?) */
    ops[0] = false;
    ops[1] = true;
    ops[2] = true;
    carry_in = ops[2];
    alu32(ops, in1, in2, &out1, &zero, &overflow);
    printf("ALU32(SUB, %d, %d) => (%d, %d, %d)\n", val1, val2, word_get_value(out1), zero, overflow);
    printf("val1 = "); word_print(in1); puts("");
    printf("val2 = "); word_print(in2); puts("");
    printf("ans  = "); word_print(out1); puts("");
    printf("check-zero is %d\n", zero);
    printf("check overflow %d\n", overflow);

    /* SLT */
    ops[0] = true;
    ops[1] = true;
    ops[2] = true;
    carry_in = ops[2];
    alu32(ops, in1, in2, &out1, &carry_out, &overflow);
    printf("ALU32(SLT, %d, %d) => %d\n", val1, val2, word_get_value(out1));
    printf("val1 = "); word_print(in1); puts("");
    printf("val2 = "); word_print(in2); puts("");
    printf("ans  = "); word_print(out1); puts("");
}
