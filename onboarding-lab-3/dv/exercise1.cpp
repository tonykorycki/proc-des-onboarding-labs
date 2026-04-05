#include <cstdint>
#include <VExercise1.h>
#include <stdio.h>


uint8_t ground_truth(uint8_t op, uint8_t a, uint8_t b) {
  switch(op) {
    case 0: return a ^ b;
    case 1: return (b >= 8) ? 0 : (uint8_t)(a << b);
    case 2: return (b == 0) ? 0 : a % b;
    case 3: return ~ (a & b);
    default: return 0;
  }
}

int main() {
  uint8_t tests_failed = 0;
  uint8_t out = 0;
  VExercise1 model;
  for(int op = 0; op < 4; ++op) {
    model.op = op;
    for(int a = 0; a < 256; ++a) {
      model.a = a;
      for(int b = 0; b < 256; ++b) {
        model.b = b;
        model.eval();
        out = model.out;
        if (out != ground_truth(op, a, b)) {
          printf("Mismatch for op %d, a %d, b %d: expected %d, got %d\n", op, a, b,
              ground_truth(op, a, b), out);
          tests_failed=1;
        }
      }
    }
  }
  return tests_failed;
}