#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>  
#include <VExercise4.h>

TEST_CASE("Exercise 4") {
  VExercise4 model;
}

TEST_CASE("Exercise 4: cs=0") {
    VExercise4 model;
    int sel = GENERATE(0, 1, 2, 3);
    model.cs = 0;
    model.sel = sel;
    for (int v = 0; v < 256; v++) {
        model.alpha = v;
        model.beta = v;
        model.gamma = v;
        model.eval();
        REQUIRE(model.out == 0);
    }
}



TEST_CASE("Exercise 4: cs=1") {
    VExercise4 model;
    model.cs = 1;
    srand(99);
    for (int i = 0; i < 1000; i++) {
        uint8_t a = rand() & 0xFF;
        uint8_t b = rand() & 0xFF;
        uint8_t g = rand() & 0xFF;

        model.alpha = a;
        model.beta  = b;
        model.gamma = g;

        model.sel = 0; model.eval();
        REQUIRE(model.out == a);

        model.sel = 1; model.eval();
        REQUIRE(model.out == b);

        model.sel = 2; model.eval();
        REQUIRE(model.out == g);

        model.sel = 3; model.eval();
        uint8_t expected = (a & (b | g));
        REQUIRE(model.out == expected);
    }

}
