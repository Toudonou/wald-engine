//
// Created by Toudonou on 16/03/2025.
//

#include <math.h>

#include "maths/we_vec2.h"
#include "core/we_log.h"

we_real we_vec2_length(const we_vec2 vec2) {
    return (we_real) sqrt(we_vec2_square_length(vec2));
}

we_real we_vec2_square_length(const we_vec2 vec2) {
    return vec2.x * vec2.x + vec2.y * vec2.y;
}

we_vec2 we_vec2_normalized(const we_vec2 vec2) {
    const we_real square_length = we_vec2_square_length(vec2);
    if (square_length == 0) {
        WE_WARN("Trying to normalize a null we_vec2");
        return (we_vec2){0, 0};
    }
    return we_vec2_scalar_mul(vec2, 1 / square_length);
}

we_vec2 we_vec2_add(const we_vec2 a, const we_vec2 b) {
    return (we_vec2){a.x + b.x, a.y + b.y};
}

we_vec2 we_vec2_sub(const we_vec2 a, const we_vec2 b) {
    return (we_vec2){a.x - b.x, a.y - b.y};
}

we_real we_vec2_dot_product(const we_vec2 a, const we_vec2 b) {
    return a.x * b.x + a.y * b.y;
}

we_vec2 we_vec2_scalar_mul(const we_vec2 vec2, const we_real scalar) {
    return (we_vec2){vec2.x * scalar, vec2.y * scalar};
}

we_bool we_vec2_are_equal(const we_vec2 a, const we_vec2 b) {
    return a.x == b.x && a.y == b.y;
}
