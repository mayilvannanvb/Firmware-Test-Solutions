
#include <stdio.h>
typedef struct {
    unsigned int P   : 1;  
    unsigned int     : 1;   
    unsigned int OV  : 1;   
    unsigned int RS0 : 1;   
    unsigned int RS1 : 1;  
    unsigned int F0  : 1;   
    unsigned int AC  : 1;   
    unsigned int CY  : 1;   
} PSW_Bits;
typedef union {
    unsigned char byte;    
    PSW_Bits      bits;    
} PSW_Register;

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
    psw.byte = 0x00;   

    printPSW("Initial PSW", &psw);
    psw.bits.CY = 1;
    printPSW("Set Carry", &psw);
    psw.bits.OV = 1;
    printPSW("Set Overflow", &psw);
    psw.bits.RS1 = 1;
    psw.bits.RS0 = 0;
    printPSW("Select Register Bank 2", &psw);
    psw.bits.CY = 0;
    printPSW("Clear Carry", &psw);
    psw.bits.AC = 1;
    printPSW("Set Auxiliary Carry", &psw);
    psw.bits.P = 1;
    printPSW("Set Parity", &psw);
    psw.byte = 0x00;
    printPSW("Reset entire PSW", &psw);
    psw.byte = 0xFF;
    printPSW("Set all bits (0xFF)", &psw);

    printf("\nsize of union  = %zu byte(s)\n", sizeof(psw));
    printf("size of byte   = %zu byte(s)\n", sizeof(psw.byte));
    printf("size of bits   = %zu byte(s)\n", sizeof(psw.bits));

    return 0;
}
