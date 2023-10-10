//
// Created by Des Caldnd on 10/10/2023.
//
#include "../functions.h"

void docs();
ld summ_hub(ld x, ld eps, ll n, ld term, ld (*next)(ld, ld, ll));
ld first_summ(ld prev_value, ld x, ll n);
ld second_summ(ld prev_value, ld x, ll n);
ld third_summ(ld prev_value, ld x, ll n);
ld fourth_summ(ld prev_value, ld x, ll n);

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        incorrect_argc(&docs);
        return 0;
    }

    enum error_type eps_error, x_error;
    ld eps = fabsl(ld_from_str(argv[1], &eps_error)), x = ld_from_str(argv[2], &x_error);

    if (eps_error == ERROR || x_error == ERROR)
    {
        printf("One of args is not a number\n\n");
        return 0;
    }

    printf("First summ with x = %LF: %LF\n\n", x, summ_hub(x, eps, 0, 1, &first_summ));
    printf("Second summ with x = %LF: %LF\n\n", x, summ_hub(x, eps, 0, 1, &second_summ));
    printf("Third summ with x = %LF: %LF\n\n", x, summ_hub(clamp(x, -1 + eps, 1 - eps), eps, 0, 1, &third_summ));
    printf("Fourth summ with x = %LF: %LF\n\n", x, summ_hub(clamp(x, -1 + eps, 1 - eps), eps, 1, -1L * x * x, &fourth_summ));
}

ld first_summ(ld prev_value, ld x, ll n)
{
    return (prev_value * x) / n;
}

ld second_summ(ld prev_value, ld x, ll n)
{
    return (prev_value * -1L * x * x) / (2 * n * (2 * n - 1));
}

ld third_summ(ld prev_value, ld x, ll n)
{
    return (prev_value * 27 * n * n * x * x) / (27 * n * n - 27 * n + 6);
}

ld fourth_summ(ld prev_value, ld x, ll n)
{
    return (prev_value * -1L * x * x * (2 * n - 2)) / (2 * n);
}

ld summ_hub(ld x, ld eps, ll n, ld term, ld (*next)(ld, ld, ll))
{
    ld summ = term;

    while (fabsl(term) > eps)
    {
        ++n;
        term = next(term, x, n);
        summ += term;
    }
    return summ;
}

void docs()
{
    printf("You must enter two float numbers: epsilon and x. In last two sums x will be clamped to (-1; 1)\n\n");
}