#include <catch2/catch_test_macros.hpp>
#include <VExercise2.h>

// TEST_CASE("Exercise 2") {
//   VExercise2 model;
// }


uint16_t ground_truth(uint16_t init) {
  uint16_t out = ((init & 0x7FFF) << 1 | (((init >> 10) & 1) ^ ((init >> 8) & 1) ^ ((init >> 3) & 1) ^ ((init >> 1) & 1)));
  return out;
}

void step(VExercise2& model) {
  model.clk ^= 1;
  model.eval();
}

void test_init_val(uint16_t test_val) {
  VExercise2 model;
  model.init = test_val;
  model.clk = 1;
  model.reset = 1;
  step(model);
  model.reset = 0;
  uint16_t curr_val = model.out;


  for(int i = 0; i < 100; i++) {
    step(model);
    step(model);
    
    REQUIRE(model.out == ground_truth(curr_val));
    curr_val = model.out;
  }
  model.reset = 1;
  step(model);
  step(model);
}


TEST_CASE("LFSR initial values") {
    uint16_t input = GENERATE(0x00, 0xFF, 0x55, 0xAA, 0x1234, 0xABCD, 0x8001, 0x7FFE);
    test_init_val(input);
}

// for(input : inputs) {
//   TEST_CASE("Initial value {input:#06x}") {
//     test_init_val(input);
//   }
// }

