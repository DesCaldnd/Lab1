//
// Created by Des Caldnd on 9/27/2023.
//
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <math.h>


enum error_type
{ correct, error };

int int_from_str(char str[], enum error_type* check_state)
{
    int result = 0;
    bool has_sign = false, has_digit = false, is_negative = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        char sym = str[i];
        if (sym >= '0' && sym <= '9')
        {
            has_sign = true;
            has_digit = true;
            result = result * 10 + (sym - '0');
        } else if ((sym == '-' || sym == '+') && !has_sign && !has_digit)
        {
            is_negative = sym == '-';
        } else
        {
            *check_state = error;
            return 0;
        }
    }
    check_state = correct;
    return is_negative ? result * -1 : result;
}

double double_from_str(char str[], enum error_type* check_state)
{
    int result_up = 0;
    double result_down = 0, prec = 10;
    bool has_sign = false, has_digit = false, is_negative = false, dot_passed = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        char sym = str[i];
        if (sym >= '0' && sym <= '9')
        {
            has_sign = true;
            has_digit = true;
            if (!dot_passed)
                result_up = result_up * 10 + (sym - '0');
            else
            {
                result_down = result_down + (double)(sym - '0') / prec;
                prec *= 10;
            }
        } else if ((sym == '-' || sym == '+') && !has_sign && !has_digit)
        {
            is_negative = sym == '-';
        } else if (sym == '.' && !dot_passed)
        {
            dot_passed = true;
        }else
        {
            *check_state = error;
            return 0;
        }
    }
    check_state = correct;
    return is_negative ? (-1.0 * (result_up + result_down)): result_up + result_down;
}

void incorrect_argc(void (*documentation_fun_ptr)())
{
    printf("You have entered incorrect number of arguments. Here is documentation below:\n");
    documentation_fun_ptr();
}

void incorrect_value(char val[])
{
    printf("\"%s\" is not a number. You must enter an integer number\n\n", val);
}

bool cmp_d(double first, double second, double precision)
{
    return fabs(first - second) < precision;
}

void swap(double *a, int i, int j)
{
    double s = a[i];
    a[i] = a[j];
    a[j] = s;
}

bool next_perm(double *a, int n)
{
    int j = n - 2;
    while (j != -1 && a[j] >= a[j + 1]) j--;
    if (j == -1)
        return false;
    int k = n - 1;
    while (a[j] >= a[k]) k--;
    swap(a, j, k);
    int l = j + 1, r = n - 1;
    while (l<r)
        swap(a, l++, r--);
    return true;
}

void sort(double *array, int size)
{
    for (int step = 0; step < size - 1; ++step) {

        for (int i = 0; i < size - step - 1; ++i) {

            if (array[i] > array[i + 1]) {

                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}