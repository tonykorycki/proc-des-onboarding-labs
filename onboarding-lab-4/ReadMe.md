# NYU ProcDesign Development Template

A template for doing SystemVerilog development for the NYU Processor Design
team.

### what is a registry?
A registry is a collection of information about packages, which are source code files that can be compiled and simulated. The registry allows you to easily manage and access these packages, making it easier to compile and simulate your code.

### what is a package?
again, packages are source code files (SV, CPP, cmake etc.) 

### difference between interface and normal library
interface packages can consist of code and files that aren timmediately compiled, like SV. some uses beyond SV include template code in cpp files, and cmake files that are used to build the code. normal libraries are compiled immediately, and can be used as dependencies for other packages.


### what is a top module?

a top module is the module that verilator exposes to the cpp testbench, and for every top module, there is a cpp file verilator generates a cpp class that the test code intantiates.