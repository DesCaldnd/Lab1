//
// Created by Des Caldnd on 9/27/2023.
//
#include "../functions.h"
#include <math.h>

//alias
typedef long double ld;


void docs();

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
    }

    ld epsilon = powl(10, precision * -1);

    return 0;
}

void docs()
{
    printf("You must have only one integer argument, which shows, how many digits after dot you want to see.\n"
           "For example 2 is 0.01");
}