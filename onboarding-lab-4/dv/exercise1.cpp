#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>

// TEST_CASE("Exercise 1") {
//   VExercise1 model;

//   // Setup some inputs
//   model.eval();

//   int expected;
//   // Calculate the expected value

//   REQUIRE(model.out == expected);
// }

int ground_truth(uint8_t op, uint8_t a, uint8_t b);

void test_op(uint8_t code, uint8_t(op)(uint8_t, uint8_t)) {
  VExercise1 model;
  model.op = code;
  model.a = 0;
  model.b = 0;

  do {
    do {
      model.eval();
      uint8_t result {op(model.a, model.b)};
      REQUIRE(result == model.out);
    } while(++model.b);
  } while(++model.a);
}

TEST_CASE("Exercise1: op = 0, XOR") {
    test_op(0, [](uint8_t a, uint8_t b) -> uint8_t { return ground_truth(0, a, b); });
}


TEST_CASE("Exercise1: op = 1, lshift") {
     test_op(1, [](uint8_t a, uint8_t b) -> uint8_t { return ground_truth(1, a, b); });

}

TEST_CASE("Exercise1: op = 2, mod") {
    test_op(2, [](uint8_t a, uint8_t b) -> uint8_t { return ground_truth(2, a, b); });

}

TEST_CASE("Exercise1: op = 3, NAND") {
    test_op(3, [](uint8_t a, uint8_t b) -> uint8_t { return ground_truth(3, a, b); });
}

int ground_truth( uint8_t op, uint8_t a, uint8_t b) {
  switch(op) {
    case 0: return a ^ b;
    case 1: return (b >= 8) ? 0 : (uint8_t)(a << b);
    case 2: return (b == 0) ? 0 : a % b;
    case 3: return ~ (a & b);
    default: return 0;
  }
}



