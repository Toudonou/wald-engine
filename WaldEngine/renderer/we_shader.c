//
// Created by Toudonou on 16/03/2025.
//

#include <glad/glad.h>
#include <stdlib.h>

#include "utils/we_file_utils.h"
#include "core/we_log.h"
#include "renderer/we_shader.h"

struct we_shader {
    we_uint32 shader_id;
};

we_shader *new_we_shader(const we_int8 *vert_path, const we_int8 *frag_path) {
    WE_ASSERT_MSG(vert_path != NULL, " the vertex shader file must be not NULL");
    WE_ASSERT_MSG(frag_path != NULL, " the fragment shader file must be not NULL");

    we_shader *shader = NULL;
    shader = calloc(1, sizeof(we_shader));
    if (shader == NULL) {
        WE_ERROR("Error when allocating memory for the shader");
        return NULL;
    }

    const we_uint32 program = glCreateProgram();
    const we_uint32 vertex = glCreateShader(GL_VERTEX_SHADER);
    const we_uint32 fragment = glCreateShader(GL_FRAGMENT_SHADER);
    we_int32 result;
    we_int8 errorLog[1024];

    we_int8 *vert_source = we_read_file(vert_path);
    we_int8 *frag_source = we_read_file(frag_path);

    if (vert_source == NULL) {
        WE_ERROR("Vertex shader source is empty.");
        return NULL;
    }

    if (frag_source == NULL) {
        WE_ERROR("Fragment shader source is empty.");
        return NULL;
    }

    // Vertex Shader
    glShaderSource(vertex, 1, (const we_int8 * const*) &vert_source, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderInfoLog(vertex, 1024, NULL, errorLog);
        WE_ERROR("Error during vertex shader compilation: %s", errorLog);
        glDeleteShader(vertex);
        return NULL;
    }

    // Fragment Shader
    glShaderSource(fragment, 1, (const we_int8 * const*) &frag_source, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderInfoLog(fragment, 1024, NULL, errorLog);
        printf("%s\n", errorLog);
        WE_ERROR("Error during fragment shader compilation: %s", errorLog);
        glDeleteShader(fragment);
        return NULL;
    }

    // Link Shaders
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramInfoLog(program, 1024, NULL, errorLog);
        WE_ERROR("Error during shader program linking: %s", errorLog);
        glDeleteProgram(program);
        return NULL;
    }

    // Validate Program
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramInfoLog(program, 1024, NULL, errorLog);
        WE_ERROR("Error during shader program validation: %s", errorLog);
        glDeleteProgram(program);
        return NULL;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vert_source);
    free(frag_source);

    shader->shader_id = program;
    return shader;
}

void destroy_we_shader(we_shader **shader) {
    if (shader == NULL || *shader == NULL) {
        WE_WARN("Trying to destroy a NULL we_shader");
        return;
    }
    glDeleteProgram((*shader)->shader_id);
    free(*shader);
    *shader = NULL;
}

void we_shader_set_uniform1i(const we_shader *shader, const we_int8 *name, const we_int32 value) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform1i(glGetUniformLocation(shader->shader_id, name), value);
}

// For an array of integer; count = number_of_elements(array)
void we_shader_set_uniform1iv(const we_shader *shader, const we_int8 *name,
                              const we_int32 *value, const we_int32 count) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform1iv(glGetUniformLocation(shader->shader_id, name), count, value);
}

void we_shader_set_uniform1f(const we_shader *shader, const we_int8 *name, const we_real value) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform1f(glGetUniformLocation(shader->shader_id, name), value);
}

void we_shader_set_uniform2f(const we_shader *shader, const we_int8 *name, const we_vec2 vector) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform2f(glGetUniformLocation(shader->shader_id, name), vector.x, vector.y);
}

void we_shader_set_uniform3f(const we_shader *shader, const we_int8 *name, const we_vec3 vector) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform3f(glGetUniformLocation(shader->shader_id, name), vector.x, vector.y, vector.z);
}

void we_shader_set_uniform4f(const we_shader *shader, const we_int8 *name, const we_vec4 vector) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniform4f(
        glGetUniformLocation(shader->shader_id, name),
        vector.x, vector.y,
        vector.z, vector.w);
}

void we_shader_set_uniform_mat4(const we_shader *shader, const we_int8 *name, const we_matrix4 matrix) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUniformMatrix4fv(glGetUniformLocation(shader->shader_id, name), 1, GL_FALSE, matrix.elements);
}

void we_shader_enable(const we_shader *shader) {
    if (shader == NULL) {
        WE_WARN("Trying to set uniform in a NULL shader");
        return;
    }
    glUseProgram(shader->shader_id);
    WE_INFO("Shader enabled");
}

void we_shader_disable() {
    glUseProgram(0);
    WE_INFO("Shader disabled");
}
