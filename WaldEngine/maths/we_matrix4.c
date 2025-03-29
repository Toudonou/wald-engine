//
// Created by Toudonou on 16/03/2025.
//

#include <string.h>

#include "maths/we_matrix4.h"
#include "core/we_log.h"
#include "maths/we_maths_functions.h"

we_matrix4 we_matrix4_diagonal(const we_real value) {
    we_matrix4 matrix4;

    memset(matrix4.elements, 0, 4 * 4 * sizeof(we_real));
    matrix4.elements[0 + 4 * 0] = value;
    matrix4.elements[1 + 4 * 1] = value;
    matrix4.elements[2 + 4 * 2] = value;
    matrix4.elements[3 + 4 * 3] = value;

    return matrix4;
}

we_matrix4 we_matrix4_identity() {
    return we_matrix4_diagonal(1);
}

we_matrix4 we_matrix4_orthographic(const we_real left, const we_real right,
                                   const we_real bottom, const we_real top,
                                   const we_real near, const we_real far) {
    we_matrix4 result = we_matrix4_identity();

    we_matrix4_set_element_at(&result, 0, 0, 2 / (right - left));
    we_matrix4_set_element_at(&result, 1, 1, 2 / (top - bottom));
    we_matrix4_set_element_at(&result, 2, 2, -2 / (far - near));

    we_matrix4_set_element_at(&result, 0, 3, -(right + left) / (right - left));
    we_matrix4_set_element_at(&result, 1, 3, -(top + bottom) / (top - bottom));
    we_matrix4_set_element_at(&result, 2, 3, -(far + near) / (far - near));

    return result;
}

we_matrix4 we_matrix4_perspective(const we_real fov, const we_real aspectRatio, const we_real near, const we_real far) {
    we_matrix4 result;

    const we_real q = 1.0f / we_tan(we_to_radians(0.5f * fov));
    const we_real a = q / aspectRatio;
    const we_real b = (near + far) / (near - far);
    const we_real c = 2 * near * far / (near - far);

    we_matrix4_set_element_at(&result, 0, 0, a);
    we_matrix4_set_element_at(&result, 1, 1, q);
    we_matrix4_set_element_at(&result, 2, 2, b);
    we_matrix4_set_element_at(&result, 2, 3, c);
    we_matrix4_set_element_at(&result, 3, 2, -1);

    return result;
}

we_matrix4 we_matrix4_translation(const we_vec3 translation) {
    we_matrix4 result = we_matrix4_identity();

    we_matrix4_set_element_at(&result, 0, 3, translation.x);
    we_matrix4_set_element_at(&result, 1, 3, translation.y);
    we_matrix4_set_element_at(&result, 2, 3, translation.z);

    return result;
}

we_matrix4 we_matrix4_scale(const we_vec3 scale) {
    we_matrix4 result = we_matrix4_identity();

    we_matrix4_set_element_at(&result, 0, 0, scale.x);
    we_matrix4_set_element_at(&result, 1, 1, scale.y);
    we_matrix4_set_element_at(&result, 2, 2, scale.z);

    return result;
}

we_matrix4 we_matrix4_rotation(const we_real angle, const we_vec3 axis) {
    we_matrix4 result = we_matrix4_identity();

    const we_real r = we_to_radians(angle);
    const we_real c = we_cos(r);
    const we_real s = we_sin(r);
    const we_real omc = 1 - c;
    const we_vec3 normalized_axis = we_vec3_normalized(axis);

    we_matrix4_set_element_at(&result, 0, 0, normalized_axis.x * normalized_axis.x * omc + c);
    we_matrix4_set_element_at(&result, 0, 1, normalized_axis.x * normalized_axis.y * omc - normalized_axis.z * s);
    we_matrix4_set_element_at(&result, 0, 2, normalized_axis.x * normalized_axis.z * omc + normalized_axis.y * s);

    we_matrix4_set_element_at(&result, 1, 0, normalized_axis.y * normalized_axis.x * omc + normalized_axis.z * s);
    we_matrix4_set_element_at(&result, 1, 1, normalized_axis.y * normalized_axis.y * omc + c);
    we_matrix4_set_element_at(&result, 1, 2, normalized_axis.y * normalized_axis.z * omc - normalized_axis.x * s);

    we_matrix4_set_element_at(&result, 2, 0, normalized_axis.z * normalized_axis.x * omc - normalized_axis.y * s);
    we_matrix4_set_element_at(&result, 2, 1, normalized_axis.z * normalized_axis.y * omc + normalized_axis.x * s);
    we_matrix4_set_element_at(&result, 2, 2, normalized_axis.z * normalized_axis.z * omc + c);

    return result;
}

we_matrix4 we_matrix4_transpose(const we_matrix4 matrix4) {
    we_matrix4 result;
    for (we_uint8 i = 0; i < 4; i++) {
        for (we_uint8 j = 0; j < 4; j++) {
            we_matrix4_set_element_at(&result, i, j, we_matrix4_get_element_at(matrix4, j, i));
        }
    }
    return result;
}

void we_matrix4_set_element_at(we_matrix4 *mat, const we_uint8 i, const we_uint8 j, const we_real value) {
    // Normal matrix4                       // OpenGL matrix4
    // m00, m01, m02, m03,  // Row 0        // m00, m10, m20, m30,  // Column 0
    // m10, m11, m12, m13,  // Row 1        // m01, m11, m21, m31,  // Column 1
    // m20, m21, m22, m23,  // Row 2        // m02, m12, m22, m32,  // Column 2
    // m30, m31, m32, m33,  // Row 3        // m03, m13, m23, m33,  // Column 3

    if (mat == NULL) {
        WE_WARN("Trying to set a value in a NULL we_matrix4");
        return;
    }
    WE_ASSERT_MSG(i >= 0 && i < 4, " i is out of bounds");
    WE_ASSERT_MSG(j >= 0 && j < 4, " j is out of bounds");
    mat->elements[i + 4 * j] = value;
}

we_real we_matrix4_get_element_at(const we_matrix4 mat, const we_uint8 i, const we_uint8 j) {
    // Normal matrix4                       // OpenGL matrix4
    // m00, m01, m02, m03,  // Row 0        // m00, m10, m20, m30,  // Column 0
    // m10, m11, m12, m13,  // Row 1        // m01, m11, m21, m31,  // Column 1
    // m20, m21, m22, m23,  // Row 2        // m02, m12, m22, m32,  // Column 2
    // m30, m31, m32, m33,  // Row 3        // m03, m13, m23, m33,  // Column 3

    WE_ASSERT_MSG(i >= 0 && i < 4, " i is out of bounds");
    WE_ASSERT_MSG(j >= 0 && j < 4, " j is out of bounds");
    return mat.elements[i + 4 * j];
}

we_matrix4 we_matrix4_add(const we_matrix4 mat1, const we_matrix4 mat2) {
    we_matrix4 result;
    for (we_int8 i = 0; i < 4 * 4; i++) {
        result.elements[i] = mat1.elements[i] + mat2.elements[i];
    }
    return result;
}

we_matrix4 we_matrix4_sub(const we_matrix4 mat1, const we_matrix4 mat2) {
    we_matrix4 result;
    for (we_int8 i = 0; i < 4 * 4; i++) {
        result.elements[i] = mat1.elements[i] - mat2.elements[i];
    }
    return result;
}

we_matrix4 we_matrix4_product(const we_matrix4 mat1, const we_matrix4 mat2) {
    we_matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                we_matrix4_set_element_at(
                    &result, i, j,
                    we_matrix4_get_element_at(result, i, j) +
                    we_matrix4_get_element_at(mat1, i, k) *
                    we_matrix4_get_element_at(mat2, k, j)
                );
            }
        }
    }
    return result;
}

we_matrix4 we_matrix4_scalar_product(const we_matrix4 mat, const we_real scalar) {
    we_matrix4 result;
    for (we_int8 i = 0; i < 4 * 4; i++) {
        result.elements[i] = mat.elements[i] * scalar;
    }
    return result;
}

we_vec4 we_matrix4_vec4_product(const we_matrix4 mat, const we_vec4 vec4) {
    we_vec4 result;

    result.x = we_matrix4_get_element_at(mat, 0, 0) * vec4.x + we_matrix4_get_element_at(mat, 0, 1) * vec4.y +
               we_matrix4_get_element_at(mat, 0, 2) * vec4.z + we_matrix4_get_element_at(mat, 0, 3) * vec4.w;

    result.y = we_matrix4_get_element_at(mat, 1, 0) * vec4.x + we_matrix4_get_element_at(mat, 1, 1) * vec4.y +
               we_matrix4_get_element_at(mat, 1, 2) * vec4.z + we_matrix4_get_element_at(mat, 1, 3) * vec4.w;

    result.z = we_matrix4_get_element_at(mat, 2, 0) * vec4.x + we_matrix4_get_element_at(mat, 2, 1) * vec4.y +
               we_matrix4_get_element_at(mat, 2, 2) * vec4.z + we_matrix4_get_element_at(mat, 2, 3) * vec4.w;

    result.w = we_matrix4_get_element_at(mat, 3, 0) * vec4.x + we_matrix4_get_element_at(mat, 3, 1) * vec4.y +
               we_matrix4_get_element_at(mat, 3, 2) * vec4.z + we_matrix4_get_element_at(mat, 3, 3) * vec4.w;

    return result;
}

we_bool we_matrix4_are_equal(const we_matrix4 mat1, const we_matrix4 mat2) {
    for (we_int8 i = 0; i < 4 * 4; i++) {
        if (mat1.elements[i] != mat2.elements[i]) return WE_FALSE;
    }
    return WE_TRUE;
}
