#include <verilated.h>
#include "obj_dir/Viob_cache.h"

#define NUM_INPUT_SET 10

int main(int argc, char **argv)
{
    Viob_cache *top = new Viob_cache;

    top->clk = 0;

    // reset
    top->reset = 1;

    for (int i = 0; i < 10; i++)
    {
        top->clk = !top->clk;
        top->eval();
    }

    top->reset = 0;
    for (int i = 0; i < 10; i++)
    {
        top->clk = !top->clk;
        top->eval();
    }

    top->ready = 0;
    for (int i = 0; i < NUM_INPUT_SET; i++)
    {
        // hook up to tools...
        // 0 <= addr <= 4095
        // wdata: 4-byte long integer
        // 0 <= wstrb <= 15
        // valid: boolean
        top->addr = 0;
        top->wdata = 0;
        top->wstrb = 0;
        top->valid = true;

        int j = 0;
        while (top->ready == 0 && ++j < 30)
        {
            // Toggle a clock
            top->clk = !top->clk;
            top->eval();
        }

        for (int k = 0; k < 4; k++)
        {
            top->clk = !top->clk;
            top->eval();
        }

        top->valid = 0;
        for (int k = 0; k < 4; k++)
        {
            top->clk = !top->clk;
            top->eval();
        }
    }

    delete top;
    return 0;
}
