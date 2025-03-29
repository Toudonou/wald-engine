//
// Created by Toudonou on 15/03/2025.
//

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "core/we_engine.h"
#include "core/we_input.h"
#include "core/we_log.h"
#include "core/we_window.h"
#include "renderer/we_renderer.h"

struct we_engine {
    we_window *window;
    we_input *input;
    we_renderer *renderer;
    we_scene *scene;
};

we_engine *new_we_engine(const we_int8 *title, const we_int32 width, const we_int32 height) {
    we_engine *engine = NULL;
    engine = calloc(1, sizeof(we_engine));
    if (engine == NULL) {
        WE_ERROR("Error during the we_engine creation");
        return NULL;
    }

    if (!glfwInit()) {
        WE_ERROR("Failed to initialize GLFW");
        free(engine);
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // TODO: Check if the components are been created correctly
    engine->window = new_we_window(title, width, height);
    engine->input = new_we_input(we_window_get_glfw_window(engine->window));

    // Should be done after the context is marked (after creating the window)
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        WE_ERROR("Failed to initialize GLAD");
        free(engine);
        return NULL;
    }

    engine->renderer = new_we_renderer(10000, engine->window);

    WE_INFO("Engine created successfully");
    return engine;
}

void destroy_we_engine(we_engine **engine) {
    if (engine == NULL || *engine == NULL) {
        WE_WARN("Trying to destroy a NULL we_engine");
        return;
    }

    destroy_we_scene(&(*engine)->scene);

    destroy_we_input(&(*engine)->input);
    destroy_we_window(&(*engine)->window);
    destroy_we_renderer(&(*engine)->renderer);

    glfwTerminate();

    free(*engine);
    *engine = NULL;
    WE_INFO("Engine destroyed successfully");
}

void we_engine_update(const we_engine *engine) {
    if (engine == NULL) {
        WE_WARN("Trying to update a NULL we_engine");
        return;
    }

    while (!we_window_is_closed(engine->window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Very important if glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        we_input_update(engine->input);
        we_renderer_flush(engine->renderer);

        if (we_scene_should_quit(engine->scene)) we_scene_update(engine->scene);
        else we_window_close(engine->window);
        we_window_update(engine->window);
    }
}

void we_engine_register_we_scene(we_engine *engine, void (*start)(we_scene *scene),
                                 void (*update)(we_scene *scene)) {
    WE_ASSERT_MSG(start != NULL, "The start function must be non NULL");
    WE_ASSERT_MSG(update != NULL, "The update function must be non NULL");

    if (engine == NULL) {
        WE_WARN("Trying to register a we_scene in a NULL we_engine");
        return;
    }

    engine->scene = new_we_scene(1, "Default Scene", start, update, engine->renderer, engine->input);
    if (engine->scene == NULL) {
        WE_WARN("Error while creating the we_scene");
        return;
    }
    we_scene_start(engine->scene);
}
