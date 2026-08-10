/*
 * Question 1: Union with PSW Register in 8051
 *
 * Models the 8051 Program Status Word (PSW) register using
 * a union — access it as a full byte OR individual bit fields.
 *
 * Compile : gcc psw_register.c -o psw
 * Run     : ./psw
 *
 * 8051 PSW Bit Layout (bit 7 to bit 0):
 *   CY | AC | F0 | RS1 | RS0 | OV | -- | P
 *   7     6    5    4     3    2    1    0
 *
 * Sample Output:
 *   Initial PSW : 0x00
 *   Set Carry    -> PSW : 0x80
 *   Set Overflow -> PSW : 0x84
 *   Select Bank2 -> PSW : 0x94
 *   Clear Carry  -> PSW : 0x14
 *
 * Concepts: Union, Bit-fields, Embedded register mapping, Bit manipulation
 */

#include <stdio.h>

/* ── PSW Bit-field struct (matches 8051 PSW layout) ─────────── */
typedef struct {
    unsigned int P   : 1;   /* bit 0 — Parity flag              */
    unsigned int     : 1;   /* bit 1 — reserved (user flag)     */
    unsigned int OV  : 1;   /* bit 2 — Overflow flag            */
    unsigned int RS0 : 1;   /* bit 3 — Register Bank select 0   */
    unsigned int RS1 : 1;   /* bit 4 — Register Bank select 1   */
    unsigned int F0  : 1;   /* bit 5 — General purpose flag     */
    unsigned int AC  : 1;   /* bit 6 — Auxiliary Carry flag     */
    unsigned int CY  : 1;   /* bit 7 — Carry flag (MSB)         */
} PSW_Bits;

/* ── Union: same memory, two views ──────────────────────────── */
typedef union {
    unsigned char byte;    /* full 8-bit register access */
    PSW_Bits      bits;    /* individual bit-field access */
} PSW_Register;

/* ── Helper: print PSW state ─────────────────────────────────── */
void printPSW(const char *label, PSW_Register *psw)
{
    printf("%-25s -> PSW : 0x%02X  "
           "[CY=%d AC=%d F0=%d RS1=%d RS0=%d OV=%d P=%d]\n",
           label, psw->byte,
           psw->bits.CY, psw->bits.AC, psw->bits.F0,
           psw->bits.RS1, psw->bits.RS0, psw->bits.OV, psw->bits.P);
}

int main(void)
{
    PSW_Register psw;
    psw.byte = 0x00;   /* clear all flags initially */

    printPSW("Initial PSW", &psw);

    /* ── Set Carry flag (bit 7) ─────────────────────────── */
    psw.bits.CY = 1;
    printPSW("Set Carry", &psw);

    /* ── Set Overflow flag (bit 2) ──────────────────────── */
    psw.bits.OV = 1;
    printPSW("Set Overflow", &psw);

    /* ── Select Register Bank 2 (RS1=1, RS0=0) ─────────── */
    psw.bits.RS1 = 1;
    psw.bits.RS0 = 0;
    printPSW("Select Register Bank 2", &psw);

    /* ── Clear Carry flag ───────────────────────────────── */
    psw.bits.CY = 0;
    printPSW("Clear Carry", &psw);

    /* ── Set Auxiliary Carry ────────────────────────────── */
    psw.bits.AC = 1;
    printPSW("Set Auxiliary Carry", &psw);

    /* ── Set Parity ─────────────────────────────────────── */
    psw.bits.P = 1;
    printPSW("Set Parity", &psw);

    /* ── Reset entire PSW via byte access ───────────────── */
    psw.byte = 0x00;
    printPSW("Reset entire PSW", &psw);

    /* ── Direct byte write to set multiple bits at once ─── */
    psw.byte = 0xFF;
    printPSW("Set all bits (0xFF)", &psw);

    printf("\nsize of union  = %zu byte(s)\n", sizeof(psw));
    printf("size of byte   = %zu byte(s)\n", sizeof(psw.byte));
    printf("size of bits   = %zu byte(s)\n", sizeof(psw.bits));

    return 0;
}
