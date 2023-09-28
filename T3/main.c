//
// Created by Des Caldnd on 9/27/2023.
//
#include "../functions.h"
#include <string.h>

enum flag_type
{q_f, m_f, t_f, undefined};

enum answer_type
{two_roots, one_root, no_root};

struct equation_answer
{
    enum answer_type state;
    double answer_1, answer_2;
};

struct four_params
{
    enum error_type state;
    double par_1, par_2, par_3, par_4;
};

struct two_params
{
    enum error_type state;
    int par_1, par_2;
};

struct four_params parse_four_params(char** argv[]);
struct two_params parse_two_params(char** argv[]);
enum flag_type get_flag_type(char[]);
void equation_hub(double, double, double, double);
struct equation_answer solve_equation(double, double [3]);
void print_eq_answer(struct equation_answer, double[3]);
void hold_print_m_flag(int, int);
enum error_type check_three_args(double a1, double a2, double a3)
{ return a1 > 0 && a2 > 0 && a3 > 0; }
bool check_right_triangle(double, double, double, double);
void print_t_flag(bool, double, double, double);
bool check_length(double, double, double);
bool check_right(double, double, double, double);
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
                struct four_params args = parse_four_params(&argv);

                if (args.state == correct)
                {
                    equation_hub(fabs(args.par_1), args.par_2, args.par_3, args.par_4);
                } else
                {
                    printf("One of args is not a number");
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
                struct two_params args = parse_two_params(&argv);

                if (args.state == correct)
                {
                    hold_print_m_flag(args.par_1, args.par_2);
                } else
                {
                    printf("One of args is not a number");
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
                struct four_params args = parse_four_params(&argv);

                if (args.state == correct)
                {
                    if (check_three_args(args.par_2, args.par_3, args.par_4))
                    {
                        print_t_flag(check_right_triangle(args.par_1, args.par_2, args.par_3, args.par_4),
                                     args.par_2, args.par_3, args.par_4);
                    } else
                    {
                        printf("One of args is less or equal to zero");
                    }
                } else
                {
                    printf("One of args is not a number");
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

bool check_right_triangle(double precision, double l_1, double l_2, double l_3)
{
    bool triangle = true, right = false;

    triangle = check_length(l_1, l_2, l_3) && check_length(l_2, l_1, l_3) && check_length(l_3, l_2, l_1);
    right = check_right(precision, l_1, l_2, l_3) || check_right(precision, l_2, l_1, l_3) || check_right(precision, l_3, l_2, l_1);

    return triangle && right;
}

void print_t_flag(bool condition, double l_1, double l_2, double l_3)
{
    printf("There can%s be right triangle with (%lf, %lf, %lf) sides\n\n", condition ? "" : " not", l_1, l_2, l_3);
}

bool check_length(double l_1, double l_2, double l_3)
{
    return l_1 < l_2 + l_3;
}

bool check_right(double precision, double l_1, double l_2, double l_3)
{
    return cmp_d(l_1 * l_1, l_2 * l_2 + l_3 * l_3, precision);
}

void equation_hub(double precision, double f1, double f2, double f3)
{
    double coeffs[3] = {f1, f2, f3};
    sort(coeffs, 3);

    struct equation_answer answer = solve_equation(precision, coeffs);
    print_eq_answer(answer, coeffs);

    while(next_perm(coeffs, 3))
    {
        answer = solve_equation(precision, coeffs);
        print_eq_answer(answer, coeffs);
    }
}

struct equation_answer solve_equation(double precision, double coeffs[3])
{
    struct equation_answer answer;

    if (cmp_d(0, coeffs[0], precision))
    {
        if (cmp_d(0, coeffs[1], precision))
        {
            answer.state = no_root;
        } else
        {
            answer.state = one_root;
            answer.answer_1 = answer.answer_2 = -1 * (coeffs[2] / coeffs[1]);
        }
        return answer;
    }

    double discriminant = coeffs[1] * coeffs[1] - 4 * coeffs[0] * coeffs[2];

    if (cmp_d(0, discriminant, precision))
    {
        answer.state = one_root;
        answer.answer_1 = answer.answer_2 = (coeffs[1] * -1) / (2 * coeffs[0]);
    } else if (discriminant > 0)
    {
        answer.state = two_roots;
        answer.answer_1 = (coeffs[1] * -1 + sqrt(discriminant)) / (2 * coeffs[0]);
        answer.answer_2 = (coeffs[1] * -1 - sqrt(discriminant)) / (2 * coeffs[0]);
    } else
    {
        answer.state = no_root;
    }
    return answer;
}

void hold_print_m_flag(int first, int second)
{
    if (first < 1 || second < 1)
    {
        printf("One or more arguments is not natural\n\n");
        return;
    }

    bool result = first % second == 0;

    printf("Number %d is%s multiple to %d\n\n", first, result ? "" : " not", second);
}

void print_eq_answer(struct equation_answer answer, double coeffs[3])
{
    printf("Solution of equation (%lf)x^2+(%lf)x+(%lf) is:\n", coeffs[0], coeffs[1], coeffs[2]);
    switch (answer.state)
    {
        case one_root:
        {
            printf("%lf\n\n", answer.answer_1);
            break;
        }
        case two_roots:
        {
            printf("%lf, %lf\n\n", answer.answer_1, answer.answer_2);
            break;
        }
        case no_root:
        {
            printf("This equation has no root\n\n");
            break;
        }
    }
}

struct four_params parse_four_params(char** argv[])
{
    struct four_params result;
    enum error_type e1, e2, e3, e4;
    result.par_1 = double_from_str((*argv)[2], &e1);
    result.par_2 = double_from_str((*argv)[3], &e2);
    result.par_3 = double_from_str((*argv)[4], &e3);
    result.par_4 = double_from_str((*argv)[5], &e4);

    if (e1 == error || e2 == error || e3 == error || e4 == error || result.par_1 == 0)
        result.state = error;
    else
        result.state = correct;

    return result;
}

struct two_params parse_two_params(char** argv[])
{
    struct two_params result;
    enum error_type e1, e2;
    result.par_1 = int_from_str((*argv)[2], &e1);
    result.par_2 = int_from_str((*argv)[3], &e2);

    if (e1 == error || e2 == error)
        result.state = error;
    else
        result.state = correct;

    return result;
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