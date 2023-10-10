//
// Created by ivanl on 09.10.2023.
//
#include "../functions.h"
#include <math.h>

void docs();
ld calculate_integral(ld (*int_function)(ld), ld epsilon);
ld first_integral(ld x);
ld second_integral(ld x);
ld third_integral(ld x);
ld fourth_integral(ld x);

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		incorrect_argc(&docs);
		return 0;
	}

	enum error_type epsilon_state;
	ld epsilon = ld_from_str(argv[1], &epsilon_state);

	if (epsilon_state == ERROR)
	{
		printf("\"%s\" in not a number\n\n");
		return 0;
	} else
	{
		printf("First integral is %.15LF\n\n", calculate_integral(&first_integral, epsilon));
		printf("First integral is %.15LF\n\n", calculate_integral(&second_integral, epsilon));
		printf("First integral is %.15LF\n\n", calculate_integral(&third_integral, epsilon));
		printf("First integral is %.15LF\n\n", calculate_integral(&fourth_integral, epsilon));
	}
}

ld calculate_integral(ld (*int_function)(ld), ld epsilon)
{
	ld x = epsilon / 2;
	ld integral_summ = 0;

	while (x < 1L)
	{
		integral_summ += int_function(x) * epsilon;

		x += epsilon;
	}

	return integral_summ;
}

ld first_integral(ld x)
{
	return logl(x + 1) / x;
}

ld second_integral(ld x)
{
	return expl(-1 * (x * x) / 2);
}

ld third_integral(ld x)
{
	return logl(1 / (1 - x));
}

ld fourth_integral(ld x)
{
	return powl(x, x);
}

void docs()
{
	printf("You must enter one float number - epsilon\n\n");
}