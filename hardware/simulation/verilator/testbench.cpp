#include <symbolica.h>
#include "obj_dir/Viob_cache.h"

#define NUM_INPUT_SET 1

int main(int argc, char **argv)
{
    Viob_cache *top = new Viob_cache;

    top->clk = 0;

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
        vluint32_t addr;
        vluint32_t wdata;
        vluint8_t wstrb;
        vluint8_t valid;

        SYMBOLIZE(addr);
        SYMBOLIZE(wdata);
        SYMBOLIZE(wstrb);
        SYMBOLIZE(valid);

        if (addr < 0 || addr > 4095)
        {
            return 0;
        }

        if (wstrb < 0 || wstrb > 15)
        {
            return 0;
        }

        if (valid < 0 || valid > 1)
        {
            return 0;
        }

        top->addr = addr;
        top->wdata = wdata;
        top->wstrb = wstrb;
        top->valid = valid;

        int j = 0;
        while (top->ready == 0 && ++j < 30)
        {
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
