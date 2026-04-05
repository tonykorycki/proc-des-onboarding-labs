#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <VExercise3.h>

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
    switch (a) {
        case 0: return ((b & 0x7) << 3) | (c & 0x7);
        case 1: return 0x40 | ((c & 0x7) << 3) | (b & 0x7);
        case 2: return b;
        default: return c;
    }
}

void clock_step(VExercise3& model) {
    model.clk ^= 1;
    model.eval();
}

int run_trial(unsigned seed) {
    srand(seed);
    VExercise3 model;

    model.a = rand() & 0xF;
    model.b = rand() & 0xFFFF;
    model.c = rand() & 0xFFFF;

    uint8_t a_in = mystery1(model.a & 0x3, model.b & 0xFF, model.c & 0xFF);
    uint8_t b_in = mystery1((model.a >> 2) & 0x3, (model.b >> 8) & 0xFF, (model.c >> 8) & 0xFF);

    model.clk = 1;
    model.reset = 1;
    model.eval();       
    clock_step(model);  
    uint16_t sim_out = ((uint16_t)b_in << 8) | a_in;
    int count = 0;

    if (model.out != sim_out) {
        printf("Reset mismatch: expected 0x%04X, got 0x%04X\n", sim_out, model.out);
        return 1;
    }

    model.reset = 0;

    for (int i = 0; i < 100; i++) {
        model.a = rand() & 0xF;
        model.b = rand() & 0xFFFF;
        model.c = rand() & 0xFFFF;

        a_in = mystery1(model.a & 0x3, model.b & 0xFF, model.c & 0xFF);
        b_in = mystery1((model.a >> 2) & 0x3, (model.b >> 8) & 0xFF, (model.c >> 8) & 0xFF);

        uint16_t prev = sim_out;
        switch (count) {
            case 0: sim_out = ((uint16_t)a_in << 8) | (prev & 0xFF); break;
            case 1: sim_out = (prev & 0xFF00) | b_in; break;
            case 2: sim_out = ((prev & 0xFF) << 8) | (prev >> 8); break;
            case 3: sim_out = ((prev & 0xF) << 12) | ((prev & 0xF0) << 4) |
                              ((prev & 0xF00) >> 4) | ((prev & 0xF000) >> 12); break;
            case 4: sim_out = __builtin_popcount(prev) & 1; break;
        }
        count = (count + 1) % 5;

        clock_step(model); 
        clock_step(model); 

        if (model.out != sim_out) {
            printf("Mismatch at cycle %d (state %d): expected 0x%04X, got 0x%04X\n",
                   i, (count + 4) % 5, sim_out, (uint16_t)model.out);
            return 1;
        }
    }

    return 0;
}

int main() {
    for (int seed = 0; seed < 5; seed++) {
        if (run_trial(seed)) return 1;
    }
    return 0;
}
