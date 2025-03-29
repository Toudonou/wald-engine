//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_MATRIX4_H
#define WE_MATRIX4_H

#include "maths/we_vec3.h"
#include "maths/we_vec4.h"

typedef struct {
    we_real elements[4 * 4];
} we_matrix4;

WE_API we_matrix4 we_matrix4_diagonal(we_real value);

WE_API we_matrix4 we_matrix4_identity();

WE_API we_matrix4 we_matrix4_orthographic(we_real left, we_real right, we_real bottom, we_real top, we_real near,
                                          we_real far);

WE_API we_matrix4 we_matrix4_perspective(we_real fov, we_real aspectRatio, we_real near, we_real far);

WE_API we_matrix4 we_matrix4_translation(we_vec3 translation);

WE_API we_matrix4 we_matrix4_scale(we_vec3 scale);

WE_API we_matrix4 we_matrix4_rotation(we_real angle, we_vec3 axis);

WE_API we_matrix4 we_matrix4_transpose(we_matrix4 matrix4);

WE_API void we_matrix4_set_element_at(we_matrix4 *mat, we_uint8 i, we_uint8 j, we_real value);

WE_API we_real we_matrix4_get_element_at(we_matrix4 mat, we_uint8 i, we_uint8 j);

WE_API we_matrix4 we_matrix4_add(we_matrix4 mat1, we_matrix4 mat2);

WE_API we_matrix4 we_matrix4_sub(we_matrix4 mat1, we_matrix4 mat2);

WE_API we_matrix4 we_matrix4_product(we_matrix4 mat1, we_matrix4 mat2);

WE_API we_matrix4 we_matrix4_scalar_product(we_matrix4 mat, we_real scalar);

WE_API we_vec4 we_matrix4_vec4_product(we_matrix4 mat, we_vec4 vec4);

WE_API we_bool we_matrix4_are_equal(we_matrix4 mat1, we_matrix4 mat2);

#endif //WE_MATRIX4_H
