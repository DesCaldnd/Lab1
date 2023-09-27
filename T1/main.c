#include <stdio.h>
#include <string.h>
#include "../functions.h"

enum flag_type
{ h_f, p_f, s_f, e_f, a_f, f_f, undefined };

enum flag_type get_flag_type(char []);
void help();
void incorrect_flag(char[]);
enum error_type check_h_flag(int);
void print_h_flag(int);
enum error_type check_p_flag(int);
void print_p_flag(int);
void print_s_flag(char[]);
void print_e_flag(int);
enum error_type check_a_flag(int);
void print_a_flag(int);
enum error_type check_f_flag(int);
void print_f_flag(int, int, enum error_type);
int factorial(int, enum error_type*);
void print_natural(int);


void print_sep(int length)
{
    for (int i = 0; i < length; ++i) {
        printf("=");
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    printf("\n");
    if(argc % 2 != 1 || argc < 3)
    {
        incorrect_argc(&help);
        return 0;
    }
    for (int i = 1; i < argc; i += 2)
    {
        enum flag_type f_type = get_flag_type(argv[i]);
        enum error_type e_type;
        int value = int_from_str(argv[i+1], &e_type);

        if (f_type == undefined)
        {
            incorrect_flag(argv[i]);
        } else if (e_type == error)
        {
            incorrect_value(argv[i+1]);
        } else
        {
            switch (f_type) {
                case h_f:
                {
                    enum error_type state = check_h_flag(value);

                    if (state == correct)
                        print_h_flag(value);
                    else
                        printf("Number %d is is out of range of [1, 100]\n\n", value);
                    break;
                }
                case p_f:
                {
                    enum error_type state = check_p_flag(value);

                    if (state == correct)
                        print_p_flag(value);
                    else
                        print_natural(value);
                    break;
                }
                case s_f:
                {
                    print_s_flag(argv[i + 1]);
                    break;
                }
                case e_f:
                {
                    print_e_flag(value);
                    break;
                }
                case a_f:
                {
                    enum error_type state = check_a_flag(value);

                    if (state == correct)
                        print_a_flag(value);
                    else
                        print_natural(value);
                    break;
                }
                case f_f:
                {
                    enum error_type state = check_f_flag(value), fact_overflow_error;

                    if (state == correct)
                    {
                        int fact = factorial(value, &fact_overflow_error);
                        print_f_flag(value, fact, fact_overflow_error);
                    } else
                        print_natural(value);
                    break;
                }
            }
        }
    }

    return 0;
}

enum error_type check_h_flag(int val)
{
    return val > 0 && val <= 100 ? correct : error;
}

void print_h_flag(int val)
{
    printf("-h flag with value %d:\n", val);
        for (int i = val; i <= 100; i += val)
        {
            printf("%d ", i);
        }
    printf("\n\n");
}

enum error_type check_p_flag(int val)
{
    return val > 0 ? correct : error;
}

void print_p_flag(int val)
{
    bool result = false;
    printf("-p flag with value %d:\n", val);
    for (int i = 2; i < val/2; ++i && !result)
    {
        if (val % i == 0)
            result = true;
    }
    printf(result ? "%d is complex\n\n" : "%d is simple\n\n", val);
}

void print_s_flag(char val[])
{
    bool digit_passed = false;

    printf("-s flag with value %s:\n", val);

    for (int i = 0; val[i] != '\0'; ++i)
    {
      if ((val[i] >= '1' && val[i] <= '9') || (val[i] == '0' && digit_passed))
      {
          digit_passed = true;
          printf("%c ", val[i]);
      } else if (val[i] == '+' || val[i] == '-')
          printf("%c ", val[i]);
    }

    if (!digit_passed)
        printf("0");

    printf("\n\n");
}

void print_e_flag(int val)
{
    if (val > 10)
        printf("Value in flag -e must be less or equal to 10, now it is %d\n\n", val);
    else
    {
        printf("-e flag with value %d:\n\n", val);
        print_sep(((3 + val) * val) / 2 + 3 * val + 1);
        for (int i = 1; i <= 10; ++i) {
            unsigned long long base = i;
            printf("|");
            for (int j = 1; j <= val; ++j) {
                printf(" %*llu |", j+1, base);
                base *= i;
            }
            printf("\n");
        }
        print_sep(((3 + val) * val) / 2 + 3 * val + 1);
        printf("\n\n");
    }

}

enum error_type check_a_flag(int val)
{
    return val > 0 ? correct : error;
}

void print_a_flag(int val)
{
    printf("-a flag with value %d:\n", val);

    printf("Sum is: %d\n\n", ((1 + val) * val) / 2);
}

enum error_type check_f_flag(int val)
{
    return val > 0 ? correct : error;
}

void print_f_flag(int val, int fact, enum error_type state)
{
    printf("-f flag with value %d:\n", val);

    if (state == correct)
        printf("Factorial of %d is %llu\n\n", val, fact);
    else
        printf("Number is too big and variable overflowed\n\n");
}

int factorial(int val, enum error_type* check_state)
{
    unsigned long long fact = 1, prev_fact = 1;
    bool not_overflowed = true;

    for (int i = 2; i <= val && not_overflowed; ++i)
    {
        prev_fact = fact;
        fact *= i;
        not_overflowed = prev_fact == fact / i;
    }
    *check_state = not_overflowed ? correct : error;
    return fact;
}

enum flag_type get_flag_type(char flag[])
{
    if (strnlen_s(flag, 4) != 2 || flag[0] != '-')
        return undefined;
    enum flag_type result;
    switch (flag[1]) {
        case 'h':
        {
            result = h_f;
            break;
        }
        case 'p':
        {
            result = p_f;
            break;
        }
        case 's':
        {
            result = s_f;
            break;
        }
        case 'e':
        {
            result = e_f;
            break;
        }
        case 'a':
        {
            result = a_f;
            break;
        }
        case 'f':
        {
            result = f_f;
            break;
        }
        default:
        {
            result = undefined;
            break;
        }
    }
    return result;
}

void incorrect_flag(char flag[])
{
    printf("\"%s\" is not a flag. Here is documentation below: ", flag);
    help();
}

void help()
{
    printf("\nYou must enter one or more pair of flag with integer value (not zero).\n"
           "Correct flags are:\n"
           "-h Prints all numbers up to 100, which are aliquot to value\n"
           "-p Prints if number is simple or complex\n"
           "-s Prints decimal place number of value\n"
           "-e Prints table of powers (1\; 10)^(1\; value)\n"
           "-a Prints sum of numbers from 1 to value\n"
           "-f Prints factorial of value\n\n");
}

void print_natural(int val)
{
    printf("Value %d must be natural\n\n", val);
}