//
// Created by Toudonou on 16/03/2025.
//

#include <math.h>

#include "we_maths_functions.h"

we_real we_to_radians(const we_real degree) {
    const we_real pi_over_180 = WE_PI / 180;
    return degree * pi_over_180;
}

we_real we_cos(const we_real angle) {
    return (we_real) cos(angle);
}

we_real we_sin(const we_real angle) {
    return (we_real) sin(angle);
}

we_real we_tan(const we_real angle) {
    return (we_real) tan(angle);
}
