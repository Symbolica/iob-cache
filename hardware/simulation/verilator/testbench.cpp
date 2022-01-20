#include <verilated.h>
#include "obj_dir/Viob_cache.h"

int main(int argc, char **argv)
{
    Viob_cache *top = new Viob_cache;

    top->clk = 0;

    // reset
    top->reset = 1;

    for (j = 0; j < 10; j++)
    {
        top->clk = !top->clk;
        top->eval();
    }

    top->reset = 0;
    for (j = 0; j < 10; j++)
    {
        top->clk = !top->clk;
        top->eval();
    }

    top->ready = 0;
    int i, j;
    for (j = 0; j < NUM_INPUT_SET; j++)
    {
        i = 0;

        // hook up to tools...
        // 0 <= addr <= 4095
        // wdata: 4-byte long integer
        // 0 <= wstrb <= 15
        // valid: boolean
        top->addr = 0;
        top->wdata = 0;
        top->wstrb = 0;
        top->valid = true;

        while (top->ready == 0 && ++i < 30)
        {
            // Toggle a clock
            top->clk = !top->clk;
            top->eval();
        }

        for (i = 0; i < 4; i++)
        {
            top->clk = !top->clk;
            top->eval();
        }

        top->valid = 0;
        for (i = 0; i < 4; i++)
        {
            top->clk = !top->clk;
            top->eval();
        }
    }

    delete top;
    exit(0);
}
