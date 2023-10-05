//
// Created by Des Caldnd on 10/3/2023.
//
#pragma once

#include "constant_functions.h"
#include <math.h>


ld e_limit(ld eps)
{
    eps = clamp_low(eps, powl(10, -9));
    ll n = round_ld(1/eps);
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
    ll n = 2;
    ld pi = 1, next_iter = 4;

    while (fabsl(pi - next_iter) > eps)
    {
        pi = next_iter;
//        next_iter *= (4.0L * n * n + 4 * n) / ((2.0L * n + 1) * (2.0L * n + 1));
        next_iter *= (4.0L * n * (n - 1)) / (4.0L * n * n - 4.0L * n + 1);
        ++n;
    }
    return pi;
}

ld pi_tailor(ld eps)
{
    eps = clamp_low(eps, powl(10, -8));
    ll n = 1;
    ld accum = 0, next_iter = 4;

    int mult = -1;

    while (fabsl(next_iter) > eps)
    {
        mult *= -1;
        next_iter = mult / (2.0L * n - 1);
        accum += next_iter;
        ++n;
    }
    return 4 * accum;
}

ld fi_func_pi(ld x)
{
    return x - (cosl(x) + 1) / (-1 * sinl(x));
}

ld pi_equation(ld eps)
{
    ld prev = 3.5L, next = fi_func_pi(prev);

    while (fabsl(prev - next) > eps)
    {
        prev = next;
        next = fi_func_pi(prev);
    }
    return next;
}


ld ln_2_limit(ld eps)
{
    int n = 2;
    ld prev = 1, next = 2;

    while (fabsl(prev - next) >  eps)
    {
        prev = next;
        ++n;
        next = n * (powl(2.0L, (1.0L / n)) - 1);
    }
    return next;
}

ld ln_2_tailor(ld eps)
{
    eps = clamp_low(eps, powl(10, -8));
    ll n = 1, mult = -1;
    ld acum = 0, next = 5;

    while (fabsl(next) > eps)
    {
        mult *= -1;
        next = mult / (ld) n;
        acum += next;
        ++n;
    }
    return acum;
}

ld ln_2_equation(ld eps)
{
    ld left = 0, right = 1, mid = 0.5L, result = 5;

    while (fabsl(result) > eps)
    {
        result = expl(mid) - 2;
        if (result < 0.0L)
            left = mid;
        else
            right = mid;

        mid = (left + right) / 2;
    }
    return mid;
}


ld sqrt_2_limit(ld eps)
{
    ld prev = -0.5, next = prev - (prev * prev) / 2 + 1;

    while (fabsl(prev - next) > eps)
    {
        prev = next;
        next = prev - (prev * prev) / 2 + 1;
    }
    return next;
}

ld sqrt_2_tailor(ld eps)
{
    ld acum = powl(2, 0.25L), power = 0.125L;
    while (power > eps)
    {
        acum *= powl(2, power);
        power *= 0.5L;
    }
    return acum;
}

ld fi_func_sqrt_2(ld x)
{
    return x - (x * x - 2) / (2 * x);
}

ld sqrt_2_equation(ld eps)
{
    ld prev = 3.5L, next = fi_func_sqrt_2(prev);

    while (fabsl(prev - next) > eps)
    {
        prev = next;
        next = fi_func_sqrt_2(prev);
    }
    return next;
}


ld gamma_limit(ld eps)
{
    eps = clamp_low(eps, powl(10, -8));
    ld acum = 0, next_iter = 1;
    ll n = 1;

    while (next_iter > eps)
    {
        ++n;
        acum += next_iter;
        next_iter = 1.0L/n;
    }
    return acum - logl(n);
}

ld gamma_tailor(ld eps)
{
    ld pi = acosl(-1);
    ld first = 1, second = 0.5L, answer = 0;
    ll n = 2, k = 2;

    while (fabsl(first - second) > eps)
    {
        if (k == n * n)
        {
            ++k;
            ++n;
        }

        first = powl(floorl(sqrtl(k)), -2);
        second = 1.0L / k;
        answer += first - second;
        ++k;
    }

    return answer - ((pi * pi) / 6);
}

void get_simple_nums()
{
    int nums_found = 0;
    ll number = 2;

    while (nums_found < SIMPLE_NUM_COUNT)
    {
        bool is_simple = true;

        for (int i = 0; i < nums_found; ++i)
        {
            if (number % simple_nums[i] == 0)
            {
                is_simple = false;
                break;
            }
        }

        if (is_simple)
        {
            simple_nums[nums_found] = number;
            nums_found++;
        }
        number++;
    }
}

ld find_limit(ld eps)
{
    ll t = 0;
    ld accum = 1, prev = 1, next = 0;

    while (fabsl(prev - next) > eps)
    {
        prev = next;
        next = (simple_nums[t] - 1.0L)/(simple_nums[t]);
        accum *= next;
        ++t;
    }
    return accum * logl(simple_nums[t]);
}

ld fi_func_gamma(ld x, ld limit)
{
    return x - (expl(-x) - limit) / (-expl(-x));
}

ld gamma_equation(ld eps)
{
    eps = clamp_low(eps, powl(10, -9));
    get_simple_nums();
    ld limit = find_limit(eps);
    ld prev = 1, next = fi_func_gamma(prev, limit);

    while (fabsl(prev - next) > eps)
    {
        prev = next;
        next = fi_func_gamma(prev, limit);
    }
    return next;
}