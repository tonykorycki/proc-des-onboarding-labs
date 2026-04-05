#include <stdio.h>
#include <VExercise2.h>


uint16_t ground_truth(uint16_t init) {
  uint16_t out = ((init & 0x7FFF) << 1 | ((init >> 10) & 1) ^ ((init >> 8) & 1) ^ ((init >> 3) & 1) ^ ((init >> 1) & 1));
  return out;
}

uint16_t inputs[] = {0x00, 0xFF, 0x55, 0xAA, 0x1234, 0xABCD, 0x8001, 0x7FFE};

void step(VExercise2& model) {
  model.clk ^= 1;
  model.eval();
}

uint8_t test_init_val(uint16_t test_val) {
  uint8_t tests_failed = 0;
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
    
    if(model.out != ground_truth(curr_val)) {
      tests_failed = 1;
      printf(
          "case filed with init val = %d, curr val = %d, expected %d, got %d \n",
          test_val, curr_val, ground_truth(curr_val), model.out);
      tests_failed = 1;
    }
    curr_val = model.out;
  }
  model.reset = 1;
  step(model);
  step(model);
  return tests_failed;
}

int main() {
  VExercise2 model;
  uint8_t tests_failed = 0;
  for(uint16_t init_val : inputs) {
    tests_failed |= test_init_val(init_val);
  }
  return tests_failed;
}
