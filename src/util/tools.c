#include "../../include/util/common.h"

#include "../../include/util/global_variables.h"
#include "../../include/util/tools.h"


double min (double a, double b) {
    return a < b ? a : b;
}

double max (double a, double b) {
    return a > b ? a : b;
}

bool checkCollision (RectD a, RectD b) {
    return a.x + a.w >= b.x && a.x <= b.x + b.w && a.y + a.h >= b.y && a.y <= b.y + b.h;
}

int fib (int n) {
    int a = 0;
    int b = 1;

    for (int i = 0; i < n-1; i++) {
        int temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}
