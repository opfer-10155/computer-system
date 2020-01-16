#include <stdio.h>
#include <mips.h>
void full_adder(Signal in1, Signal in2, Signal carry_in, Signal *out1, Signal *carry_out)
{
    /* Exercise 5-2 */
    // sum
    Signal inner1;
    xor_circuit(in1, in2, &inner1);
    xor_circuit(inner1, carry_in, out1);
    // carry_out
    Signal inner2;
    Signal inner3;
    and_gate(in1, in2, &inner2);
    xor_circuit(in1, in2, &inner3);
    and_gate(inner3, carry_in, &inner3);
    or_gate(inner2, inner3, carry_out);
}

void rca(Word in1, Word in2, Signal carry_in, Word *out1, Signal *carry_out)
{
    /* Excercise 5-3 */
    for (int i = 0; i < 32; i++) {
        full_adder(in1.bit[i], in2.bit[i], carry_in, out1->bit+i, carry_out);
        carry_in = *carry_out;
    }
}

void test_full_adder()
{
    /* Exercise 5-2 */
    Signal out1;
    Signal carry_out;
    for (Signal in1 = 0; in1 <= 1; in1++) {
        for(Signal in2 = 0; in2 <= 1; in2++) {
            for(Signal carry_in = 0; carry_in <= 1; carry_in++) {
                full_adder(in1, in2, carry_in, &out1, &carry_out);
                printf("in1 = %d in2 = %d carry_in = %d\n", in1, in2, carry_in);
                printf("carry_out = %d, sum = %d\n", carry_out, out1);
                printf("%d + %d + %d = %d%d\n", in1, in2, carry_in, carry_out, out1);
            }
        }
    }
}

void int_to_word(int x, Word *a) {
    a->bit[31] = 0;
    int tmp = x >= 0 ? x : -x;
    for(int i=0; i < 31; i++) {
        a->bit[i] = tmp % 2;
        tmp /= 2;
    }
    if (x < 0) {
        for(int i=0; i < 32; i++) {
            a->bit[i] = 1 - a->bit[i];
        }
        Word one = {{1}};
        Signal null;
        rca(*a, one, 0, a, &null);
    }
}

void word_print(Word a) {
    for(int i=31; i >= 0; i--) {
        printf("%d", a.bit[i]);
    }
}

void test_rca(int val1, int val2)
{
    /* Excercise 5-3 */
    Word a, b, out;
    Signal carry_out;
    int_to_word(val1, &a);
    int_to_word(val2, &b);
    printf("a = "); word_print(a); printf("(%d)\n", val1);
    printf("b = "); word_print(b); printf("(%d)\n", val2);
    rca(a, b, 0, &out, &carry_out);
    printf("sum = "); word_print(out); printf("(%d)\n", val1 + val2);
    printf("carry_out = %d\n", carry_out);
}

void pfa(Signal a, Signal b, Signal carry_in, Signal *g, Signal *p, Signal *s) {
    and_gate(a, b, &g);
    or_gate(a, b, &p);
    Signal inner1;
    xor_circuit(a, b, &inner1);
    xor_circuit(inner1, carry_in, &s);
}

void cla(Signal g0, Signal p0, Signal g1, Signal p1, Signal g2, Signal p2, Signal g3, Signal p3, Signal carry_in,
            Signal *c1, Signal *c2, Signal *c3, Signal *carry_out, Signal G, Signal P)
    {
        Signal inner0;
        and_gate(p0, c0, &inner0);
        or_gate(g0, inner0, c1);

        and_gate(p1, c1, &inner0);
        or_gate(g1, inner0, c2);

        and_gate(p2, c2, &inner0);
        or_gate(g2, inner0, c3);

        and_gate(p3, c3, &inner0);
        or_gate(g3, inner0, carry_out);
    }