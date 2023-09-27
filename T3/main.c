//
// Created by Des Caldnd on 9/27/2023.
//
#include "../functions.h"
#include <string.h>

enum flag_type
{q_f, m_f, t_f, undefined};

enum flag_type get_flag_type(char[]);
void docs();

int main(int argc, char* argv[])
{
    if (argc < 4)
    {
        incorrect_argc(&docs);
        return 0;
    }
    enum flag_type f_type = get_flag_type(argv[1]);

    switch (f_type)
    {
        case q_f:
        {
            if (argc != 6)
            {
                incorrect_argc(&docs);
            } else
            {
                enum error_type e1, e2, e3, e4;
                double precision = double_from_str(argv[2], e1), f1 = double_from_str(argv[3], e2);
                double f2 = double_from_str(argv[4], e3), f3 = double_from_str(argv[5], e4);

                if (e1 == error || e2 == error || e3 == error || e4 == error)
                {
                    printf("One of arguments is not a number");
                } else
                {

                }
            }
            break;
        }
        case m_f:
        {
            if (argc != 4)
            {
                incorrect_argc(&docs);
            } else
            {
                enum error_type e1, e2;
                double precision = double_from_str(argv[2], e1), f1 = double_from_str(argv[3], e2);

                if (e1 == error || e2 == error)
                {
                    printf("One of arguments is not a number");
                } else
                {

                }
            }
            break;
        }
        case t_f:
        {
            if (argc != 6)
            {
                incorrect_argc(&docs);
            } else
            {
                enum error_type e1, e2, e3, e4;
                double precision = double_from_str(argv[2], e1), f1 = double_from_str(argv[3], e2);
                double f2 = double_from_str(argv[4], e3), f3 = double_from_str(argv[5], e4);

                if (e1 == error || e2 == error || e3 == error || e4 == error)
                {
                    printf("One of arguments is not a number");
                } else
                {

                }
            }
            break;
        }
        default:
        {
            printf("%s is not a flag\n", argv[1]);
            break;
        }
    }

}

enum flag_type get_flag_type(char flag[])
{
    if (strnlen_s(flag, 4) != 2 || flag[0] != '-')
        return undefined;
    enum flag_type result;
    switch (flag[1]) {
        case 'q':
        {
            result = q_f;
            break;
        }
        case 'm':
        {
            result = m_f;
            break;
        }
        case 't':
        {
            result = t_f;
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

void docs()
{
    printf("You must enter only one flag with it`s parameters:\n"
           "-q - (precision, float, float, float) solves quadratic equations with indices of all args unique permutations\n"
           "-m - (float, float) checks if first number is multiple to second\n"
           "-t - (precision, float, float, float) checks if it can be right triangle with such sides\n\n");
}