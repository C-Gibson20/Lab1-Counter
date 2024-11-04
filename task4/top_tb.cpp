#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);
    Vtop* top = new Vtop;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("top.vcd");

    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab 1 Counter");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    for (i=0; i<100; i++){

        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }

        vbdHex(4, (int(top->bcd) >> 16) & 0xF);
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, int(top->bcd) & 0xF);
        vbdCycle(i+1);

        top->rst = 0;
        top->en = vbdFlag();
        top->v = vbdValue(); 
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}