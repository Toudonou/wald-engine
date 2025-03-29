//
// Created by Toudonou on 16/03/2025.
//

#include <stdlib.h>

#include "utils/we_file_utils.h"

#include <string.h>

#include "core/we_log.h"
#include "core/containers/we_vector.h"

we_int8 *we_read_file(const we_int8 *file_name) {
    we_int8 *result = NULL;

    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        WE_ERROR("Error during file opening : %s", file_name);
        return NULL;
    }

    we_vector_int8 *temp_result = new_we_vector_int8();
    we_int32 c;
    while ((c = getc(file)) != WE_EOF) {
        we_vector_int8_push_back(temp_result, (we_int8) c);
    }

    result = (we_int8 *) calloc(temp_result->size, sizeof(we_int8));
    if (result == NULL) {
        WE_ERROR("Error during the allocation of memory for the file %s", file_name);
        delete_we_vector_int8(&temp_result);
        fclose(file);
        return NULL;
    }
    memcpy(result, temp_result->data, temp_result->size * sizeof(we_int8));

    fclose(file);
    delete_we_vector_int8(&temp_result);
    return result;
}
