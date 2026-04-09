#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <VExercise3.h>

// TEST_CASE("Exercise 3") {
//   VExercise3 model;
// }

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
    switch (a) {
        case 0: return ((b & 0x7) << 3) | (c & 0x7);
        case 1: return 0x40 | ((c & 0x7) << 3) | (b & 0x7);
        case 2: return b;
        default: return c;
    }
}

uint16_t mystery2(int count, uint16_t prev, uint8_t a_in, uint8_t b_in) {
    switch (count) {
        case 0: return ((uint16_t)a_in << 8) | (prev & 0xFF);
        case 1: return (prev & 0xFF00) | b_in;
        case 2: return ((prev & 0xFF) << 8) | (prev >> 8);
        case 3: return ((prev & 0xF) << 12) | ((prev & 0xF0) << 4) |
                       ((prev & 0xF00) >> 4) | ((prev & 0xF000) >> 12);
        case 4: return __builtin_popcount(prev) & 1;
        default: return prev;
    }
}


void clock_step(VExercise3& model) {
    model.clk ^= 1;
    model.eval();
}

TEST_CASE("Exercise 3") {
  unsigned seed = GENERATE(0, 1, 2, 3, 4);  
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

    REQUIRE(model.out == sim_out);

    model.reset = 0;

    for (int i = 0; i < 100; i++) {
        model.a = rand() & 0xF;
        model.b = rand() & 0xFFFF;
        model.c = rand() & 0xFFFF;

        a_in = mystery1(model.a & 0x3, model.b & 0xFF, model.c & 0xFF);
        b_in = mystery1((model.a >> 2) & 0x3, (model.b >> 8) & 0xFF, (model.c >> 8) & 0xFF);

        uint16_t prev = sim_out;
        sim_out = mystery2(count, prev, a_in, b_in);
        count = (count + 1) % 5;


        clock_step(model); 
        clock_step(model); 

        REQUIRE(model.out == sim_out);
    }

}
