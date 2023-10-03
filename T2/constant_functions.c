//
// Created by Des Caldnd on 10/3/2023.
//
#include "constant_functions.h"
#include <math.h>

ld e_limit(ld eps)
{
    ll n = 1/eps;
    ld answer, fraction = eps;

    answer = power_ld_int(1 + fraction, n);
    return answer;
}

ld e_tailor(ld eps)
{
    ll fact = 1;
    int index = 0;
    ld row_summ = 0;

    while (1.0L/fact > eps)
    {
        row_summ += 1.0L/fact;
        ++index;
        fact *= index;
    }
    return row_summ;
}

ld e_equation(ld eps)
{
    ld left = 2, right = 3, middle, result;

    while (fabsl(left - right) > eps)
    {
        middle = (left + right) / 2;

        result = logl(middle) - 1;

        if (result < 0L)
            left = middle;
        else
            right = middle;
    }
    return middle;
}


ld pi_limit(ld eps)
{

}

ld pi_tailor(ld eps)
{

}

ld pi_equation(ld eps)
{

}


ld ln_2_limit(ld eps)
{

}

ld ln_2_tailor(ld eps)
{

}

ld ln_2_equation(ld eps)
{

}


ld sqrt_2_limit(ld eps)
{

}

ld sqrt_2_tailor(ld eps)
{

}

ld sqrt_2_equation(ld eps)
{

}


ld gamma_limit(ld eps)
{

}

ld gamma_tailor(ld eps)
{

}

ld gamma_equation(ld eps)
{

}