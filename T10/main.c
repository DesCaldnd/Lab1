//
// Created by Des Caldnd on 10/1/2023.
//
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "../functions.h"

int char_to_int(char sym);
bool is_char_correct(char sym, int radix);

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
        tmp = integer_from_n_radix(input_number, radix, &error_return, &char_to_int, &is_char_correct);
        if (error_return == CORRECT)
        {
            has_correct_number_entered = true;
            max_number = tmp;
        }

        printf("Enter numbers in systems with yor radix or Stop:");
        scanf("%s", &input_number);

        while (strcmp(input_number, "Stop"))
        {
            tmp = integer_from_n_radix(input_number, radix, &error_return, &char_to_int, &is_char_correct);
            if (error_return == CORRECT)
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
        printf("You haven`t entered any CORRECT number");
    }
}

int char_to_int(char sym)
{
	if (isalnum(sym)) {
		return isdigit(sym) ? sym - '0' : sym - 'A' + 10;
	}

	return -1;
}

bool is_char_correct(char sym, int radix)
{
    int tmp = char_to_int(sym);
    return tmp >= 0 && tmp < radix;
}