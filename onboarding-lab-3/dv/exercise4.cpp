#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <VExercise4.h>

int main() {
    VExercise4 model;

    for (int sel = 0; sel < 4; sel++) {
        for (int v = 0; v < 256; v++) {
            model.cs = 0;
            model.sel = sel;
            model.alpha = v;
            model.beta = v;
            model.gamma = v;
            model.eval();
            if (model.out != 0) {
                printf("cs=0 fail: sel=%d alpha=%d out=%d\n", sel, v, model.out);
                return 1;
            }
        }
    }
    srand(99);
    for (int i = 0; i < 1000; i++) {
        uint8_t a = rand() & 0xFF;
        uint8_t b = rand() & 0xFF;
        uint8_t g = rand() & 0xFF;

        model.cs = 1;
        model.alpha = a;
        model.beta  = b;
        model.gamma = g;

        model.sel = 0; model.eval();
        if (model.out != a) {
            printf("sel=0 fail: expected %d got %d\n", a, model.out); return 1;
        }

        model.sel = 1; model.eval();
        if (model.out != b) {
            printf("sel=1 fail: expected %d got %d\n", b, model.out); return 1;
        }

        model.sel = 2; model.eval();
        if (model.out != g) {
            printf("sel=2 fail: expected %d got %d\n", g, model.out); return 1;
        }

        model.sel = 3; model.eval();
        uint8_t expected = a & (b | g);
        if (model.out != expected) {
            printf("sel=3 fail: expected %d got %d\n", expected, model.out); return 1;
        }
    }

    return 0;
}
