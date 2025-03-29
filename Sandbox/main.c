#include <stdio.h>
#include <stdlib.h>

#include "core/containers/we_vector.h"
#include "core/we_engine.h"
#include "core/we_log.h"
#include "maths/we_maths_functions.h"
#include "scene/we_entity.h"
#include "scene/we_scene.h"

// TODO: Make an iterator on hash_map

void rect_entity_start(we_uint32 entity_id, we_entity *entity, we_scene *scene) {
    if (entity == NULL || scene == NULL) {
        WE_WARN("Trying to start a NULL we_entity in a NULL we_scene");
        return;
    }
    entity->transform.position = (we_vec2){100, 100};

    we_scene_attach_rect_component_to_entity(entity_id, scene, (we_rectangle){
                                                 .name = "Rectangle 1",
                                                 .width = 100,
                                                 .height = 100,
                                                 .offset = (we_vec2){0, 0},
                                                 .color = (we_color){1, 0, 0, 1}
                                             });

    we_scene_attach_rect_component_to_entity(entity_id, scene, (we_rectangle){
                                                 .name = "Rectangle 2",
                                                 .width = 100,
                                                 .height = 100,
                                                 .offset = (we_vec2){100, 100},
                                                 .color = (we_color){0, 1, 0, 1}
                                             });
}

void rect_entity_update(we_uint32 entity_id, we_entity *entity, we_scene *scene) {
    if (entity == NULL || scene == NULL) {
        WE_WARN("Trying to update a NULL we_entity in a NULL we_scene");
        return;
    }

    const we_input *input = we_scene_get_input(scene);
    const we_real speed = 5;

    we_vec2 direction = {0, 0};
    we_vec2 velocity = {0, 0};

    if (we_input_is_key_down(input, LEFT)) {
        direction.x = -1;
    } else if (we_input_is_key_down(input, RIGHT)) {
        direction.x = 1;
    }

    if (we_input_is_key_down(input, UP)) {
        direction.y = -1;
    } else if (we_input_is_key_down(input, DOWN)) {
        direction.y = 1;
    }

    direction = we_vec2_normalized(direction);
    velocity = we_vec2_scalar_mul(direction, speed);

    entity->transform.position = we_vec2_add(entity->transform.position, velocity);
}

void scene_start(we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to start a NULL we_scene");
        return;
    }
    we_scene_add_entity_to_we_scene(scene, "Rect Entity", rect_entity_start, rect_entity_update);
}

void scene_update(we_scene *scene) {
    if (scene == NULL) {
        WE_WARN("Trying to update a NULL we_scene");
        return;
    }
    const we_input* input = we_scene_get_input(scene);
    if (we_input_is_key_down(input, ESCAPE)) {
        we_scene_quit(scene);
    }
}

int main() {
    we_engine *engine = new_we_engine("Platformer", 1080, 640);
    if (engine == NULL) {
        WE_ERROR("Error during the creation of the engine");
        return -1;
    }
    we_engine_register_we_scene(engine, scene_start, scene_update);
    we_engine_update(engine);
    destroy_we_engine(&engine);

    return 0;
}
