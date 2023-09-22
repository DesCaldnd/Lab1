#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void help();
void incorrect_argc();
void incorrect_flag(char[]);
void incorrect_value(char[]);
void h_flag(int);
void p_flag(int);
void s_flag(char[]);
void e_flag(int);
void a_flag(int);
void f_flag(int);

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
        incorrect_argc();
        return 0;
    }
    for (int i = 1; i < argc; i += 2)
    {
        int value = abs(atoi(argv[i+1]));
        if (strnlen_s(argv[i], 4) != 2 || argv[i][0] != '-')
        {
            incorrect_flag(argv[i]);
        } else if (!value)
        {
            incorrect_value(argv[i+1]);
        } else
        {
            switch (argv[i][1]) {
                case 'h':
                {
                    h_flag(value);
                    break;
                }
                case 'p':
                {
                    p_flag(value);
                    break;
                }
                case 's':
                {
                    s_flag(argv[i+1]);
                    break;
                }
                case 'e':
                {
                    e_flag(value);
                    break;
                }
                case 'a':
                {
                    a_flag(value);
                    break;
                }
                case 'f':
                {
                    f_flag(value);
                    break;
                }
                default:
                {
                    incorrect_flag(argv[i]);
                    break;
                }
            }
        }
    }

    return 0;
}


void h_flag(int val)
{
    printf("-h flag with value %d:\n", val);
    if (val > 100)
    {
        printf("Number %d is too big. It must be less or equal to 100", val);
    } else
        for (int i = val; i <= 100; i += val)
        {
            printf("%d ", i);
        }
    printf("\n\n");
}

void p_flag(int val)
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

void s_flag(char val[])
{
    bool digit_passed = false;
    unsigned int len = strnlen_s(val, 100);

    printf("-s flag with value %s:\n", val);

    for (int i = 0; i < len; ++i)
    {
      if ((val[i] >= '1' && val[i] <= '9') || (val[i] == '0' && digit_passed))
      {
          digit_passed = true;
          printf("%c ", val[i]);
      } else if (val[i] == '+' || val[i] == '-')
          printf("%c ", val[i]);
    }
    printf("\n\n");
}

void e_flag(int val)
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

void a_flag(int val)
{
    printf("-a flag with value %d:\n", val);

    printf("Sum is: %d\n\n", ((1 + val) * val) / 2);
}

void f_flag(int val)
{
    printf("-f flag with value %d:\n", val);
    unsigned long long fact = 1, prev_fact = 1;
    bool not_overflowed = true;

    for (int i = 2; i <= val && not_overflowed; ++i)
    {
        prev_fact = fact;
        fact *= i;
        not_overflowed = prev_fact == fact / i;
    }

    if (not_overflowed)
        printf("Factorial of %d is %llu\n\n", val, fact);
    else
        printf("Number is too big and variable overflowed\n\n");
}

void incorrect_value(char val[])
{
    printf("\"%s\" is not a number. You must enter an integer number\n\n", val);
}

void incorrect_flag(char flag[])
{
    printf("\"%s\" is not a flag. Here is documentation below: ", flag);
    help();
}

void incorrect_argc()
{
    printf("You have entered incorrect number of arguments. Here is documentation below: ");
    help();
}

void help()
{
    printf("\nYou must enter one or more pair of flag with integer value (not zero).\n"
           "Correct flags are:\n"
           "-h Prints all numbers up to 100, which are aliquot to value (uses abs)\n"
           "-p Prints if number is simple or complex (uses abs)\n"
           "-s Prints decimal place number of value (uses abs)\n"
           "-e Prints table of powers (1\; 10)^(1\; value) (uses abs)\n"
           "-a Prints sum of numbers from 1 to value (uses abs)\n"
           "-f Prints factorial of value (uses abs)\n\n");
}