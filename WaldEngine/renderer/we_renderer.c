//
// Created by Toudonou on 16/03/2025.
//

#include <glad/glad.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "components/we_components.h"
#include "core/we_defines.h"
#include "core/we_log.h"
#include "core/we_window.h"
#include "maths/we_vec2.h"
#include "maths/we_vec3.h"
#include "renderer/we_renderer.h"
#include "renderer/we_shader.h"

struct we_renderer {
    we_uint32 vao;
    we_uint32 max_renderable;
    we_uint32 vbo;
    we_uint32 ibo;
    we_window *window;
    we_vector_vertex *vertices;
    we_map_rectangle *rectangle_map;
    we_shader *shader;
};


we_int8 NUM_SPRITE_VERTICES = 4;
we_int8 NUM_SPRITE_INDICES = 6;

WE_API void we_renderer_begin(const we_renderer *renderer);

WE_API void we_renderer_end(const we_renderer *renderer);

we_renderer *new_we_renderer(const we_uint32 max_renderable, we_window *window) {
    WE_ASSERT_MSG(window, "the window passed to the renderer must be not NULL");

    we_renderer *renderer = NULL;
    renderer = (we_renderer *) calloc(1, sizeof(we_renderer));
    if (renderer == NULL) {
        WE_ERROR("Error during the creation of the renderer");
        return NULL;
    }

    renderer->max_renderable = max_renderable;
    renderer->window = window;
    renderer->vertices = new_we_vector_vertex();
    renderer->rectangle_map = new_we_map_rectangle();

    // TODO: Should be re-built
    renderer->shader = new_we_shader("/media/toudonou/Oswald/Dev/WaldEngine/WaldEngine/renderer/shaders/vert.glsl",
                                     "/media/toudonou/Oswald/Dev/WaldEngine/WaldEngine/renderer/shaders/frag.glsl");

    if (renderer->vertices == NULL) {
        WE_WARN("Error during the allocation of memory for the vertices");
        destroy_we_renderer(&renderer);
        return NULL;
    }
    if (renderer->rectangle_map == NULL) {
        WE_WARN("Error during the allocation of memory for the hashmap in the renderer");
        destroy_we_renderer(&renderer);
        return NULL;
    }
    if (renderer->shader == NULL) {
        WE_WARN("Error during the allocation of memory for the shader in the renderer");
        destroy_we_renderer(&renderer);
        return NULL;
    }

    // Enable the shader
    we_shader_enable(renderer->shader);

    const GLint textures[32] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
        29, 30, 31
    };
    // TODO: Should be re-built
    we_shader_set_uniform1iv(renderer->shader, "textures", textures, 32);

    // VAO
    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    // VBO
    glGenBuffers(1, &renderer->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr) (renderer->max_renderable * NUM_SPRITE_VERTICES * sizeof(we_vertex)),
                 NULL,GL_DYNAMIC_DRAW);

    // Layout attribution
    // position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, position)));

    // uv
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, uv)));

    // color
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, color)));

    // texture_index
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, texture_index)));

    // center
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, center)));

    // radius
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(we_vertex), (void *) (offsetof(we_vertex, radius)));

    // IBO
    we_vector_uint32 *indices = new_we_vector_uint32();
    if (indices == NULL) {
        WE_WARN("Error during the allocation of memory for the indices vector in the renderer");
        destroy_we_renderer(&renderer);
        return NULL;
    }
    we_vector_uint32_resize(indices, renderer->max_renderable * NUM_SPRITE_INDICES);

    // Populating the vector to change his actual size
    for (we_uint32 i = 0; i < renderer->max_renderable * NUM_SPRITE_INDICES; i++) {
        we_vector_uint32_push_back(indices, i);
    }

    we_uint32 offset = 0;
    /*
        0----2
        |   /|
        |  / |
        | /  |
        1----3
    */
    for (we_uint32 i = 0; i < renderer->max_renderable * NUM_SPRITE_INDICES; i += NUM_SPRITE_INDICES) {
        we_uint32 indice_value = 0 + offset;
        we_vector_uint32_insert_at(indices, i + 0, indice_value);

        indice_value = 1 + offset;
        we_vector_uint32_insert_at(indices, i + 1, indice_value);

        indice_value = 2 + offset;
        we_vector_uint32_insert_at(indices, i + 2, indice_value);

        indice_value = 1 + offset;
        we_vector_uint32_insert_at(indices, i + 3, indice_value);

        indice_value = 2 + offset;
        we_vector_uint32_insert_at(indices, i + 4, indice_value);

        indice_value = 3 + offset;
        we_vector_uint32_insert_at(indices, i + 5, indice_value);

        offset += NUM_SPRITE_VERTICES;
    }

    glGenBuffers(1, &renderer->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ibo);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, (we_int64) (renderer->max_renderable * NUM_SPRITE_INDICES * sizeof(we_uint32)),
        we_vector_uint32_get_data(indices),GL_DYNAMIC_DRAW);

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    WE_INFO("Renderer created successfully");
    return renderer;
}

void destroy_we_renderer(we_renderer **renderer) {
    if (renderer == NULL || *renderer == NULL) {
        WE_WARN("Trying to delete a NULL we_renderer");
        return;
    }

    we_shader_disable();

    glDeleteVertexArrays(1, &(*renderer)->vao);
    glDeleteBuffers(1, &(*renderer)->vbo);
    glDeleteBuffers(1, &(*renderer)->ibo);

    destroy_we_shader(&(*renderer)->shader);
    delete_we_vector_vertex(&(*renderer)->vertices);
    delete_we_map_rectangle(&(*renderer)->rectangle_map);

    free(*renderer);
    *renderer = NULL;
    WE_INFO("Renderer destroyed successfully");
}

void we_renderer_flush(const we_renderer *renderer) {
    if (renderer == NULL) {
        WE_WARN("Trying to flush a NULL we_renderer");
        return;
    }

    we_renderer_begin(renderer);

    // Erase all the vertices with the new ones
    glBufferSubData(GL_ARRAY_BUFFER, 0, (we_int64) (we_vector_vertex_get_size(renderer->vertices) * sizeof(we_vertex)),
                    we_vector_vertex_get_data(renderer->vertices));

    // Draw the elements : 1 quad = 2 triangles = 4 vertices = 6 indices => all quads = number of quad * 6 / 4
    // NUM_SPRITE_INDICES = 6 / NUM_SPRITE_VERTICES = 4 => 6 / 4 = 1.5
    const we_real indices_factor = (we_real) NUM_SPRITE_INDICES / (we_real) NUM_SPRITE_VERTICES;
    glDrawElements(GL_TRIANGLES, (we_int32) (indices_factor * (we_real) we_vector_vertex_get_size(renderer->vertices)),
                   GL_UNSIGNED_INT, NULL);

    we_renderer_end(renderer);
}

void we_renderer_attach_rectangle_to_entity(const we_renderer *renderer, const we_uint32 entity_id,
                                            const we_rectangle rectangle) {
    if (renderer == NULL) {
        WE_WARN("Trying to add a rectangle to a NULL we_renderer");
        return;
    }
    we_map_rectangle_insert_at(renderer->rectangle_map, entity_id, rectangle);
}

void we_renderer_update_components_position_by_entity_id(const we_renderer *renderer, const we_uint32 entity_id,
                                                         const we_vec2 entity_position) {
    if (renderer == NULL) {
        WE_WARN("Trying to update components position in a NULL we_renderer");
        return;
    }

    // Rectangles components
    we_vector_rectangle *rects_vector = we_map_rectangle_get_element_at(renderer->rectangle_map, entity_id);
    for (we_uint32 j = 0; j < we_vector_rectangle_get_size(rects_vector); j++) {
        rects_vector->data[j].position = we_vec2_add(
            entity_position,
            rects_vector->data[j].offset
        );
        rects_vector->data[j].position.y = we_window_get_size(renderer->window).y - rects_vector->data[j].position.y;
    }
}

// Private functions
void we_renderer_begin(const we_renderer *renderer) {
    if (renderer == NULL) {
        WE_WARN("Trying to start the drawing with a NULL we_renderer");
        return;
    }

    // Important for having good image rendering
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Enable the depth test to be able to use z coordinate as z-index
    glEnable(GL_DEPTH_TEST);

    // Bind everything
    glBindVertexArray(renderer->vao);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->ibo);

    we_shader_set_uniform_mat4(
        renderer->shader,
        "pr_matrix",
        we_matrix4_orthographic(0, we_window_get_size(renderer->window).x,
                                0, we_window_get_size(renderer->window).y,
                                -10, 10
        )
    );

    for (we_uint32 i = 0; i < we_map_rectangle_get_size(renderer->rectangle_map); i++) {
        we_vector_rectangle *rect_vector = we_map_rectangle_get_element_at(renderer->rectangle_map, i);
        if (rect_vector != NULL) {
            for (we_uint32 j = 0; j < we_vector_rectangle_get_size(rect_vector); j++) {
                we_rectangle rect = we_vector_rectangle_get_element_at(rect_vector, j);
                /*
                    0----2
                    |   /|
                    |  / |
                    | /  |
                    1----3
                */
                we_vertex vertex;
                vertex.uv = (we_vec2){0, 0};
                vertex.color = rect.color;
                vertex.center = (we_vec3){0, 0, 0};
                vertex.radius = -1;
                vertex.texture_index = -1;

                // TODO: Take the z-index of the entity in account

                // 0
                vertex.position = (we_vec3){rect.position.x - rect.width / 2, rect.position.y - rect.height / 2, 0};
                we_vector_vertex_push_back(renderer->vertices, vertex);

                // 1
                vertex.position = (we_vec3){rect.position.x - rect.width / 2, rect.position.y + rect.height / 2, 0};
                we_vector_vertex_push_back(renderer->vertices, vertex);

                // 2
                vertex.position = (we_vec3){rect.position.x + rect.width / 2, rect.position.y - rect.height / 2, 0};
                we_vector_vertex_push_back(renderer->vertices, vertex);

                // 3
                vertex.position = (we_vec3){rect.position.x + rect.width / 2, rect.position.y + rect.height / 2, 0};
                we_vector_vertex_push_back(renderer->vertices, vertex);
            }
        }
    }
}

void we_renderer_end(const we_renderer *renderer) {
    if (renderer == NULL) {
        WE_WARN("Trying to end the drawing with a NULL we_renderer");
        return;
    }

    // Unbind everything
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    we_vector_vertex_erase(renderer->vertices);
}
