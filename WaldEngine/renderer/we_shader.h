//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_SHADER_H
#define WE_SHADER_H

#include "core/we_defines.h"
#include "maths/we_maths.h"

typedef struct we_shader we_shader;

WE_API we_shader *new_we_shader(const we_int8* vert_path, const we_int8* frag_path);

WE_API void destroy_we_shader(we_shader **shader);

WE_API void we_shader_set_uniform1i(const we_shader *shader, const we_int8 *name, we_int32 value);

WE_API void we_shader_set_uniform1iv(const we_shader *shader, const we_int8 *name, const we_int32 *value, we_int32 count);

WE_API void we_shader_set_uniform1f(const we_shader *shader, const we_int8 *name, we_real value);

WE_API void we_shader_set_uniform2f(const we_shader *shader, const we_int8 *name, const we_vec2 vector);

WE_API void we_shader_set_uniform3f(const we_shader *shader, const we_int8 *name, const we_vec3 vector);

WE_API void we_shader_set_uniform4f(const we_shader *shader, const we_int8 *name, const we_vec4 vector);

WE_API void we_shader_set_uniform_mat4(const we_shader *shader, const we_int8 *name, const we_matrix4 matrix);

WE_API void we_shader_enable(const we_shader *shader);

WE_API void we_shader_disable();

#endif //WE_SHADER_H
