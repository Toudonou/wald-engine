//
// Created by Toudonou on 23/03/2025.
//

#include <stdlib.h>
#include <string.h>

#include "scene/we_scene.h"
#include "core/we_input.h"
#include "core/we_log.h"
#include "core/containers/we_vector.h"
#include "renderer/we_renderer.h"

typedef struct we_entity_wrapper {
    we_uint32 id;
    we_entity entity;

    void (*start)(we_uint32 entity_id, we_entity *entity, we_scene *scene);

    void (*update)(we_uint32 entity_id, we_entity *entity, we_scene *scene);
} we_entity_wrapper;

DEFINE_WE_VECTOR(we_entity_wrapper, entity_wrapper)

struct we_scene {
    we_uint32 id;
    we_int8 name[WE_MAX_WE_SCENE_NAME_LENGTH];
    we_bool is_running;
    we_vector_entity_wrapper *entities; // This will hold we_entity_wrapper
    we_renderer *renderer;
    we_input *input;

    void (*start)(we_scene *scene);

    void (*update)(we_scene *scene);
};

we_scene *new_we_scene(const we_uint32 id, const we_int8 *name,
                       void (*start)(we_scene *scene), void (*update)(we_scene *scene),
                       we_renderer *renderer, we_input *input) {
    WE_ASSERT_MSG(start != NULL, "The start function must be non NULL");
    WE_ASSERT_MSG(update != NULL, "The update function must be non NULL");
    WE_ASSERT_MSG(renderer != NULL, "The renderer must be non NULL");
    WE_ASSERT_MSG(input != NULL, "The input must be non NULL");

    we_scene *new_scene = NULL;
    new_scene = (we_scene *) calloc(1, sizeof(we_scene));
    if (new_scene == NULL) {
        WE_ERROR("Error while allocating memory for the scene %s", name);
        return NULL;
    }

    new_scene->id = id;
    memcpy(new_scene->name, name, WE_MIN(WE_MAX_WE_SCENE_NAME_LENGTH, strlen(name)) * sizeof(we_int8));
    new_scene->name[WE_MAX_WE_SCENE_NAME_LENGTH - 1] = '\0';
    new_scene->is_running = WE_FALSE;

    new_scene->entities = new_we_vector_entity_wrapper();

    new_scene->input = input;
    new_scene->renderer = renderer;

    new_scene->start = start;
    new_scene->update = update;

    return new_scene;
}

void destroy_we_scene(we_scene **scene) {
    if (scene == NULL || *scene == NULL) {
        WE_WARN("Trying to delete a NULL we_scene");
        return;
    }

    delete_we_vector_entity_wrapper(&(*scene)->entities);

    (*scene)->is_running = WE_FALSE;
    (*scene)->start = NULL;
    (*scene)->update = NULL;
    (*scene)->renderer = NULL;
    (*scene)->input = NULL;

    free(*scene);
    *scene = NULL;
}

void we_scene_start(we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to start a NULL we_scene");
        return;
    }
    if (scene->start == NULL) {
        WE_WARN("Trying to start an we_scene with a NULL start function");
        return;
    }

    scene->start(scene);
    scene->is_running = WE_TRUE;
}

void we_scene_update(we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to update a NULL we_scene");
        return;
    }
    if (scene->update == NULL) {
        WE_WARN("Trying to update an we_scene with a NULL update function");
        return;
    }

    for (we_uint32 i = 0; i < we_vector_entity_wrapper_get_size(scene->entities); i++) {
        we_renderer_update_components_position_by_entity_id(
            scene->renderer, scene->entities->data[i].id,
            scene->entities->data[i].entity.transform.position
        );
        scene->entities->data[i].update(scene->entities->data[i].id, &scene->entities->data[i].entity, scene);
    }
    scene->update(scene);
}

void we_scene_quit(we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to quit a NULL we_scene");
        return;
    }
    scene->is_running = WE_FALSE;
}

we_bool we_scene_should_quit(const we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to know if a NULL we_scene should quit");
        return WE_TRUE;
    }
    return scene->is_running;
}

we_renderer *we_scene_get_renderer(const we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to get a we_renderer from a NULL we_scene");
        return NULL;
    }
    return scene->renderer;
}

we_input *we_scene_get_input(const we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to get a we_input from a NULL we_scene");
        return NULL;
    }
    return scene->input;
}

void we_scene_add_entity_to_we_scene(we_scene *scene, const we_int8 *name,
                                     void (*start)(we_uint32 entity_id, we_entity *entity, we_scene *scene),
                                     void (*update)(we_uint32 entity_id, we_entity *entity, we_scene *scene)) {
    if (scene == NULL) {
        WE_WARN("Trying to add an we_entity to a NULL we_scene");
        return;
    }

    // No we_entity will have an id of 0
    we_entity_wrapper entity_wrapper = {
        .id = we_vector_entity_wrapper_get_size(scene->entities),
        .entity = {
            .name = {0},
            .z_index = 0,
            .transform = {
                .position = {0, 0},
                .scale = {1, 1},
                .rotation = 0
            }
        },
        .start = start,
        .update = update
    };
    memcpy(entity_wrapper.entity.name, name, WE_MIN(WE_MAX_WE_ENTITY_NAME_LENGTH, strlen(name)) * sizeof(we_int8));
    entity_wrapper.entity.name[WE_MAX_WE_ENTITY_NAME_LENGTH - 1] = '\0';

    we_vector_entity_wrapper_push_back(scene->entities, entity_wrapper);

    // TODO: You should think about this part
    const we_uint32 id = entity_wrapper.id;
    scene->entities->data[id].start(scene->entities->data[id].id, &scene->entities->data[id].entity, scene);
}

void we_scene_attach_rect_component_to_entity(const we_uint32 entity_id, const we_scene *scene,
                                              const we_rectangle rectangle) {
    if (scene == NULL) {
        WE_WARN("Trying to attach a rectangle component to an entity in a NULL we_scene");
        return;
    }

    we_renderer_attach_rectangle_to_entity(scene->renderer, entity_id, rectangle);
}

void delete_entity_in_we_scene(we_scene *scene, const we_uint8 *name) {
}
