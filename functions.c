//
// Created by Des Caldnd on 10/3/2023.
//
#include "functions.h"

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

void swap_int(int *l, int *r)
{
    int tmp = *l;
    *l = *r;
    *r = tmp;
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

void sort_double_bubble(double *array, int size)
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

ll integer_from_n_radix(char *string, int radix, enum error_type* error_return, char (*char_to_int)(char), bool (*is_char_correct)(char, int))
{
    ll result = 0, multiplier = 1;
    bool has_sign_entered = false, is_negative = false;
    int length = strnlen_s(string, 64);

    for(int i = length - 1; i >= 0; --i)
    {
        if (is_char_correct(string[i], radix) && !has_sign_entered)
        {
            result += char_to_int(string[i]) * multiplier;
            multiplier *= radix;
        } else if ((string[i] == '+' || string[i] == '-') && !has_sign_entered)
        {
            is_negative = string[i] == '-';
            has_sign_entered = true;
        } else
        {
            *error_return = error;
            return 0;
        }
    }
    *error_return = correct;
    return is_negative ? result * -1 : result;
}

ld power_ld_int(ld base, unsigned int pow)
{
    ld result = 1, last_multiplier = base;

    unsigned int index = 0;

    for (int i = 0; i < sizeof(unsigned int) * 8; ++i)
    {
        if (pow & 1u << i)
        {
            for (int j = index; j < i; ++j)
            {
                ++index;
                last_multiplier *= last_multiplier;
            }
            result *= last_multiplier;
        }
    }
    return result;
}