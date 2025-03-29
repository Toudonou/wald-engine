//
// Created by Toudonou on 23/03/2025.
//

#ifndef WE_SCENE_H
#define WE_SCENE_H

#include "core/we_defines.h"
#include "core/we_input.h"
#include "renderer/we_renderer.h"
#include "scene/we_entity.h"

typedef struct we_scene we_scene;

WE_API we_scene *new_we_scene(we_uint32 id, const we_int8 *name,
                              void (*start)(we_scene *scene), void (*update)(we_scene *scene),
                              we_renderer *renderer, we_input *input);

WE_API void destroy_we_scene(we_scene **scene);

WE_API void we_scene_start(we_scene *scene);

WE_API void we_scene_update(we_scene *scene);

WE_API void we_scene_quit(we_scene *scene);

WE_API we_bool we_scene_should_quit(const we_scene *scene);

WE_API we_input *we_scene_get_input(const we_scene *scene);

WE_API void we_scene_add_entity_to_we_scene(we_scene *scene, const we_int8 *name,
                                            void (*start)(we_uint32 entity_id, we_entity *entity, we_scene *scene),
                                            void (*update)(we_uint32 entity_id, we_entity *entity, we_scene *scene));

WE_API void we_scene_attach_rect_component_to_entity(we_uint32 entity_id, const we_scene *scene,
                                                     we_rectangle rectangle);

WE_API void we_scene_attach_circle_component_to_entity(we_uint32 entity_id, const we_scene *scene,
                                                       const we_circle circle);

WE_API void we_scene_attach_sprite_component_to_entity(we_uint32 entity_id, const we_scene *scene,
                                                       const we_sprite sprite);

WE_API void we_scene_draw_rectangle(const we_scene *scene, we_rectangle rectangle);

WE_API void we_scene_draw_circle(const we_scene *scene, const we_circle circle);

WE_API void delete_entity_in_we_scene(we_scene *scene, const we_uint8 *name);

#endif //WE_SCENE_H
