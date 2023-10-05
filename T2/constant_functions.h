//
// Created by Des Caldnd on 10/3/2023.
//

#include "../functions.h"

#define SIMPLE_NUM_COUNT 4654

ld e_limit(ld eps);
ld e_tailor(ld eps);
ld e_equation(ld eps);

ld pi_limit(ld eps);
ld pi_tailor(ld eps);
ld pi_equation(ld eps);

ld fi_func_pi(ld x);

ld ln_2_limit(ld eps);
ld ln_2_tailor(ld eps);
ld ln_2_equation(ld eps);

ld sqrt_2_limit(ld eps);
ld sqrt_2_tailor(ld eps);
ld sqrt_2_equation(ld eps);

ld fi_func_sqrt_2(ld x);

ll simple_nums[SIMPLE_NUM_COUNT];

void get_simple_nums();
ld find_limit(ld eps);
ld fi_func_gamma(ld x, ld limit);

ld gamma_limit(ld eps);
ld gamma_tailor(ld eps);
ld gamma_equation(ld eps);