//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_VEC2_H
#define WE_VEC2_H

#include "core/we_defines.h"

typedef struct {
    we_real x;
    we_real y;
} we_vec2;

WE_API we_real we_vec2_length(we_vec2 vec2);

WE_API we_real we_vec2_square_length(we_vec2 vec2);

WE_API we_vec2 we_vec2_normalized(we_vec2 vec2);

WE_API we_vec2 we_vec2_add(we_vec2 a, we_vec2 b);

WE_API we_vec2 we_vec2_sub(we_vec2 a, we_vec2 b);

WE_API we_real we_vec2_dot_product(we_vec2 a, we_vec2 b);

WE_API we_vec2 we_vec2_scalar_mul(we_vec2 vec2, we_real scalar);

WE_API we_bool we_vec2_are_equal(we_vec2 a, we_vec2 b);

#endif //WE_VEC2_H
