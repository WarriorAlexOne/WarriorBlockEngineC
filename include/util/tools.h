#ifndef TOOLS_H
#define TOOLS_H

#include "../../include/util/global_variables.h"

#define min min   // VS Code was angry with this function name, so this is defined to get rid of the error squiggles.
#define max max   // VS Code was angry with this function name, so this is defined to get rid of the error squiggles.


double min (double a, double b);
double max (double a, double b);
bool checkCollision (RectF item1, RectF item2);
int fib (int n);

#endif