//
// Created by Toudonou on 17/03/2025.
//

#include <stdlib.h>

#include "utils/we_string.h"
#include "core/we_log.h"

struct we_string {
    we_vector_int8 *content;
};

we_string *new_string() {
    we_string *string = NULL;
    string = (we_string *) calloc(1, sizeof(we_string));
    if (string == NULL) {
        WE_ERROR("Error while allocating memory for the we_string");
        return NULL;
    }

    string->content = new_we_vector_int8();
    if (string->content == NULL) {
        delete_we_string(&string);
        return NULL;
    }

    return string;
}

void we_string_append(const we_string *string, const we_int8 c) {
    if (string == NULL) {
        WE_WARN("Trying to add a character to a NULL we_string");
        return;
    }
    we_vector_int8_push_back(string->content, c);
}

const we_int8 *we_string_get_content(const we_string *string) {
    if (string == NULL) {
        WE_WARN("Trying to some content from a NULL we_string");
        return NULL;
    }
    return string->content->data;
}

void delete_we_string(we_string **string) {
    if (string == NULL || *string == NULL) {
        WE_WARN("Trying to destroy a NULL we_string");
        return;
    }
    delete_we_vector_int8(&(*string)->content);
    free(*string);
    *string = NULL;
}
