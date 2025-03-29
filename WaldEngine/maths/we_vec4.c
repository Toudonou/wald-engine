//
// Created by Toudonou on 16/03/2025.
//

#include <math.h>

#include "maths/we_vec4.h"
#include "core/we_log.h"

we_real we_vec4_length(const we_vec4 vec4) {
    return (we_real) sqrt(we_vec4_square_length(vec4));
}

we_real we_vec4_square_length(const we_vec4 vec4) {
    return vec4.x * vec4.x + vec4.y * vec4.y + vec4.z * vec4.z + vec4.w * vec4.w;
}

we_vec4 we_vec4_normalized(const we_vec4 vec4) {
    const we_real square_length = we_vec4_square_length(vec4);
    if (square_length == 0) {
        WE_WARN("Trying to normalize a null we_vec4");
        return (we_vec4){0, 0, 0, 0};
    }
    return we_vec4_scalar_mul(vec4, 1 / square_length);
}

we_vec4 we_vec4_add(const we_vec4 a, const we_vec4 b) {
    return (we_vec4){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

we_vec4 we_vec4_sub(const we_vec4 a, const we_vec4 b) {
    return (we_vec4){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

we_real we_vec4_dot_product(const we_vec4 a, const we_vec4 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w + b.w;
}

we_vec4 we_vec4_scalar_mul(const we_vec4 vec4, const we_real scalar) {
    return (we_vec4){vec4.x * scalar, vec4.y * scalar, vec4.z * scalar, vec4.w * scalar};
}

we_bool we_vec4_are_equal(const we_vec4 a, const we_vec4 b) {
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}
