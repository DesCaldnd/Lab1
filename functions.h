//
// Created by Des Caldnd on 9/27/2023.
//
#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

typedef long long ll;
typedef long double ld;

enum error_type
{ correct, error };

int int_from_str(char str[], enum error_type* check_state);

double double_from_str(char str[], enum error_type* check_state);

void incorrect_argc(void (*documentation_fun_ptr)());

void incorrect_value(char val[]);

bool cmp_d(double first, double second, double precision);

void swap(double *a, int i, int j);

void swap_int(int *l, int *r);

bool next_perm(double *array, int length);

void sort_double_bubble(double *array, int size);

ll integer_from_n_radix(char *string, int radix, enum error_type* error_return, char (*char_to_int)(char), bool (*is_char_correct)(char, int));

ld power_ld_int(ld base, unsigned int pow);

ll round_ld(ld number);

ld clamp_low(ld number, ld border);