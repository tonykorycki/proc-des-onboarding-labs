# Week 2 Lab: System Verilog

Fill out this readme as required by lab guidance

Tests passed! had to change some stuff in the cmake files and testbenches though.

Tests for exercise 1 are exaustive since its a small input space and we can test every combination of inputs. this gives us most confidence but scales poorly.

For exercise 2 we have 2^16 possible states so we just test a handful of inputs that should cover important cases. this is much faster and gives us some confidence but we could be missing some edge cases.

for exercise 3, we also have a lot of states so we just test a handful of random inputs and check that the output matches our model. this is the fastest but we have the least confidence since we could be missing some important edge cases. but the randomness gives pretty good coverage.