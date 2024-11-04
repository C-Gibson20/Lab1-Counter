#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

enum State {
    COUNTING,
    FREEZING
};

int main(int argc, char **argv, char **env) {
    int i;
    int clk;
    State state = COUNTING;
    int freeze_counter = 0;

    Verilated::commandArgs(argc, argv);
    Vcounter* top = new Vcounter;

    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99);
    tfp->open ("counter.vcd");

    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    for (i=0; i<300; i++){

        for (clk=0; clk<2; clk++) {
            tfp->dump (2*i+clk);
            top->clk = !top->clk;
            top->eval ();
        }
        top->rst = (i < 2) | (i == 15);
        top->en = (i > 4);

        switch (state) {
            case COUNTING:
                if (top->count == 9) {
                    state = FREEZING;
                    freeze_counter = 3;
                }
                top->en = (i > 4);
                break;

            case FREEZING:
                top->en =0;
                freeze_counter--;
                if (freeze_counter == 0) {
                    state = COUNTING;
                }
                break;
        }
        
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}