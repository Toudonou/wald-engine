//
// Created by Toudonou on 16/03/2025.
//

#include <math.h>

#include "maths/we_vec3.h"
#include "core/we_log.h"

we_real we_vec3_length(const we_vec3 vec3) {
    return (we_real) sqrt(we_vec3_square_length(vec3));
}

we_real we_vec3_square_length(const we_vec3 vec3) {
    return vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z;
}

we_vec3 we_vec3_normalized(const we_vec3 vec3) {
    const we_real square_length = we_vec3_square_length(vec3);
    if (square_length == 0) {
        WE_WARN("Trying to normalize a null we_vec3");
        return (we_vec3){0, 0, 0};
    }
    return we_vec3_scalar_mul(vec3, 1 / square_length);
}

we_vec3 we_vec3_add(const we_vec3 a, const we_vec3 b) {
    return (we_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

we_vec3 we_vec3_sub(const we_vec3 a, const we_vec3 b) {
    return (we_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

we_real we_vec3_dot_product(const we_vec3 a, const we_vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

we_vec3 we_vec3_cross_product(const we_vec3 a, const we_vec3 b) {
    return (we_vec3){.x = a.y * b.z - a.z * b.y, .y = a.z * b.x - a.x * b.z, .z = a.x * b.y - a.y * b.x};
}

we_vec3 we_vec3_scalar_mul(const we_vec3 vec3, const we_real scalar) {
    return (we_vec3){vec3.x * scalar, vec3.y * scalar, vec3.z * scalar};
}

we_bool we_vec3_are_equal(const we_vec3 a, const we_vec3 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
