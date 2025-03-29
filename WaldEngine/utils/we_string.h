//
// Created by Toudonou on 17/03/2025.
//

#ifndef WE_STRING_H
#define WE_STRING_H

#include "core/we_defines.h"
#include "core/containers/we_vector.h"

// TODO: Re-think the string implementation

typedef struct we_string we_string;

WE_API we_string *new_string();

WE_API void we_string_append(const we_string *string, we_int8 c);

WE_API const we_int8 *we_string_get_content(const we_string *string);

WE_API void delete_we_string(we_string **string);

#endif //WE_STRING_H
