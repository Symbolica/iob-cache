#include <verilated.h>

#include "obj_dir/Viob_cache.h"

int main(int argc, char** argv) {

    Viob_cache* tb = new Viob_cache; // Create UUT

    tb->reset = 0; // Init wire to initial value

    int main_time = 0;
    while (!Verilated::gotFinish()) {
        if (main_time > 10) {
            tb->reset = 1;
        }
        if ((main_time % 10) == 1) {
            tb->clk = 1;
        }
        if ((main_time % 10) == 6) {
            tb->clk = 0;
        }
        tb->eval();
        main_time++;

        // Stop after a set time, since otherwise the current design would simulate forever
        if(main_time > 100){
            break;
        }
    }

    tb->final();

    delete tb;

    return 0;
}
