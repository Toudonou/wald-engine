//
// Created by Toudonou on 16/03/2025.
//

#ifndef WE_RENDERER_H
#define WE_RENDERER_H

#include "components/we_components.h"
#include "core/we_defines.h"
#include "core/we_window.h"
#include "core/containers/we_hash_map.h"
#include "core/containers/we_vector.h"

typedef struct {
    we_real texture_index;
    we_real radius;
    we_vec2 uv;
    we_color color;
    we_vec3 position;
    we_vec3 center;
} we_vertex;

typedef struct we_renderer we_renderer;

WE_API we_renderer *new_we_renderer(we_uint32 max_renderable, we_window *window);

WE_API void destroy_we_renderer(we_renderer **renderer);

WE_API void we_renderer_flush(const we_renderer *renderer);

WE_API void we_renderer_attach_rectangle_to_entity(const we_renderer *renderer, we_uint32 entity_id,
                                                   we_rectangle rectangle);

WE_API void we_renderer_update_components_position_by_entity_id(const we_renderer *renderer, we_uint32 entity_id,
                                                                we_vec2 entity_position);

DEFINE_WE_VECTOR(we_vertex, vertex)

DEFINE_WE_VECTOR(we_rectangle, rectangle)

DEFINE_WE_MAP(we_rectangle, rectangle)

#endif//WE_RENDERER_H
