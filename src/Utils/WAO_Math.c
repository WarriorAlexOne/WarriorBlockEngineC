#include "Utils/WAO_Math.h"

long long fib (long long index) {
    if (index < 1) return 0;
    long long temp = 0;
    long long a = 0;
    long long b = 1;

    while (index > 0) {
        temp = a + b;
        a = b;
        b = temp;
        index--;
    }
    return a;
}
