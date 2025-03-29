//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_VEC4_H
#define WE_VEC4_H

#include "core/we_defines.h"

typedef struct {
    we_real x;
    we_real y;
    we_real z;
    we_real w;
} we_vec4;

WE_API we_real we_vec4_length(we_vec4 vec4);

WE_API we_real we_vec4_square_length(we_vec4 vec4);

WE_API we_vec4 we_vec4_normalized(we_vec4 vec4);

WE_API we_vec4 we_vec4_add(we_vec4 a, we_vec4 b);

WE_API we_vec4 we_vec4_sub(we_vec4 a, we_vec4 b);

WE_API we_real we_vec4_dot_product(we_vec4 a, we_vec4 b);

WE_API we_vec4 we_vec4_scalar_mul(we_vec4 vec4, we_real scalar);

WE_API we_bool we_vec4_are_equal(we_vec4 a, we_vec4 b);

#endif //WE_VEC4_H
