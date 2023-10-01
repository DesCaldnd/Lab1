//
// Created by Des Caldnd on 10/1/2023.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../functions.h"

typedef long long ll;

ll integer_from_n_radix(char *string, int radix, enum error_type* error_return);
void integer_to_n_radix(ll number, int radix, char* string);
int char_to_int(char sym);
bool is_char_correct(char sym, int radix);
char int_to_char(int num);

int main()
{
    printf("Enter radix (integer) in range from 2 to 36:");
    int radix;
    scanf("%d", &radix);

    if (radix < 2 || radix > 36)
    {
        printf("Radix is out of range\n");
        return 0;
    }

    char input_number[64];
    ll max_number, tmp;
    bool has_correct_number_entered = false;
    enum error_type error_return;
    printf("Enter numbers in systems with yor radix or Stop:");
    scanf("%s", &input_number);

    if (strcmp(input_number, "Stop"))
    {
        tmp = integer_from_n_radix(input_number, radix, &error_return);
        if (error_return == correct)
        {
            has_correct_number_entered = true;
            max_number = tmp;
        }

        printf("Enter numbers in systems with yor radix or Stop:");
        scanf("%s", &input_number);

        while (strcmp(input_number, "Stop"))
        {
            tmp = integer_from_n_radix(input_number, radix, &error_return);
            if (error_return == correct)
            {
                has_correct_number_entered = true;
                if (tmp > max_number)
                    max_number = tmp;
            }
            printf("Enter numbers in systems with yor radix or Stop:");
            scanf("%s", &input_number);
        }
    }
    if (has_correct_number_entered)
    {
        integer_to_n_radix(max_number, 9, &input_number);
        printf("Max number with 9 base: %s\n\n", input_number);
        integer_to_n_radix(max_number, 18, &input_number);
        printf("Max number with 18 base: %s\n\n", input_number);
        integer_to_n_radix(max_number, 27, &input_number);
        printf("Max number with 27 base: %s\n\n", input_number);
        integer_to_n_radix(max_number, 36, &input_number);
        printf("Max number with 36 base: %s\n\n", input_number);
    } else
    {
        printf("You haven`t entered any correct number");
    }
}

ll integer_from_n_radix(char *string, int radix, enum error_type* error_return)
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

void integer_to_n_radix(ll number, int radix, char* string)
{
    int length = logl(number) / logl(radix);
    int counter = 1;
    ++length;

    if (number < 0)
    {
        string[0] = '-';
        ++length;
    }
    string[length] = '\0';
    number = llabs(number);

    while(number)
    {
        int tmp = number % radix;
        number /= radix;
        string[length - counter] = int_to_char(tmp);
        counter++;
    }
}

char int_to_char(int num)
{
    if (num <= 9)
        return num + '0';
    else
        return num - 10 + 'A';
}

int char_to_int(char sym)
{
    if (sym >= '0' && sym <= '9')
        return sym - '0';
    else if (sym >= 'A' && sym <= 'Z')
        return sym - 'A' + 10;
    else
        return -1;
}

bool is_char_correct(char sym, int radix)
{
    int tmp = char_to_int(sym);
    return tmp >= 0 && tmp < radix;
}