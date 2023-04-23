#include "tinyexpr.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    const char *c = "fact(5)";
    double r = te_interp(c, 0);
    printf("Expressão:\n\t%s\nResultado:\n\t%f\n", c, r);
    return 0;
}