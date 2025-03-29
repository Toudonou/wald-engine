//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_VEC3_H
#define WE_VEC3_H

#include "core/we_defines.h"

typedef struct {
    we_real x;
    we_real y;
    we_real z;
} we_vec3;

WE_API we_real we_vec3_length(we_vec3 vec3);

WE_API we_real we_vec3_square_length(we_vec3 vec3);

WE_API we_vec3 we_vec3_normalized(we_vec3 vec3);

WE_API we_vec3 we_vec3_add(we_vec3 a, we_vec3 b);

WE_API we_vec3 we_vec3_sub(we_vec3 a, we_vec3 b);

WE_API we_real we_vec3_dot_product(we_vec3 a, we_vec3 b);

WE_API we_vec3 we_vec3_cross_product(we_vec3 a, we_vec3 b);

WE_API we_vec3 we_vec3_scalar_mul(we_vec3 vec3, we_real scalar);

WE_API we_bool we_vec3_are_equal(we_vec3 a, we_vec3 b);


#endif //WE_VEC3_H
