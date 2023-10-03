//
// Created by Des Caldnd on 9/27/2023.
//
#include "../functions.h"
#include <math.h>
#include "constant_functions.h"


void docs();
void print_three_constants(ld limit, ld taylor, ld equation, int precision);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        incorrect_argc(&docs);
        return 0;
    }

    enum error_type is_integer;
    int precision = int_from_str(argv[1], &is_integer);

    if (is_integer == error)
    {
        incorrect_value(argv[1]);
        return 0;
    }

    if (precision < 1)
    {
        printf("Precision must be natural number\n\n");
        return 0;
    } else if (precision > 18)
    {
        printf("Precision is too big\n\n");
        docs();
        return 0;
    }

    ld epsilon = powl(10, precision * -1);


    printf("Exponent:\n");
    print_three_constants(e_limit(epsilon), e_tailor(epsilon), e_equation(epsilon), precision);

    printf("Pi:\n");
    print_three_constants(pi_limit(epsilon), pi_tailor(epsilon), pi_equation(epsilon), precision);

    printf("Ln2:\n");
    print_three_constants(ln_2_limit(epsilon), ln_2_tailor(epsilon), ln_2_equation(epsilon), precision);

    printf("Sqrt2:\n");
    print_three_constants(sqrt_2_limit(epsilon), sqrt_2_tailor(epsilon), sqrt_2_equation(epsilon), precision);

    printf("Gamma:\n");
    print_three_constants(gamma_limit(epsilon), gamma_tailor(epsilon), gamma_equation(epsilon), precision);
    return 0;
}


void print_three_constants(ld limit, ld taylor, ld equation, int precision)
{
    printf("Limit: %.*LF | Taylor: %.*LF | Equation: %.*LF\n\n", precision, limit, precision, taylor, precision, equation);
}

void docs()
{
    printf("You must have only one integer argument in range [1, 18], which shows, how many digits after dot you want to see.\n"
           "For example 2 is 0.01\n\n");
}