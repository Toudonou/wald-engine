//
// Created by Toudonou on 15/03/2025.
//

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <string.h>

#include "core/we_log.h"
#include "core/we_window.h"

struct we_window {
    GLFWwindow *window;
    we_int32 width;
    we_int32 height;
    we_int8 title[WE_MAX_WE_WINDOW_NAME_LENGTH];
};

we_int32 we_global_width = 0;
we_int32 we_global_height = 0;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    we_global_width = width;
    we_global_height = height;
}

we_window *new_we_window(const we_int8 *title, const we_int32 width, const we_int32 height) {
    WE_ASSERT_MSG(title != NULL, " the window must have a valid tilte");
    WE_ASSERT_MSG(width > 0, " the window width must be greater than 0");
    WE_ASSERT_MSG(height > 0, " the window height must be greater than 0");

    we_window *window = NULL;
    window = calloc(1, sizeof(we_window));
    if (window == NULL) {
        WE_ERROR("Error during the creation of the window");
        return NULL;
    }

    window->width = width;
    window->height = height;

    we_global_width = width;
    we_global_height = height;

    memcpy(window->title, title, strlen(title));
    window->title[WE_MAX_WE_WINDOW_NAME_LENGTH - 1] = '\0';

    window->window = glfwCreateWindow(window->width, window->height, window->title, NULL, NULL);
    if (window->window == NULL) {
        WE_ERROR("Error while creating the GLFWWindow");
        free(window);
        return NULL;
    }
    glfwSetWindowSizeCallback(window->window, framebuffer_size_callback);
    glfwMakeContextCurrent(window->window);

    WE_INFO("Window created successfully");
    return window;
}

void destroy_we_window(we_window **window) {
    if (window == NULL || *window == NULL) {
        WE_WARN("Trying to destroy a NULL we_window");
        return;
    }
    glfwDestroyWindow((*window)->window);
    free(*window);
    *window = NULL;
    WE_INFO("Window destroyed successfully");
}

WE_API void we_window_update(we_window *window) {
    if (window == NULL) {
        WE_WARN("Trying to update a NULL we_window");
        return;
    }

    window->width = we_global_width;
    window->height = we_global_height;

    glfwSwapBuffers(window->window);
}

GLFWwindow *we_window_get_glfw_window(const we_window *window) {
    if (window == NULL) {
        WE_WARN("Trying to get GLFWwindow from a NULL we_window");
        return NULL;
    }
    return window->window;
}

WE_API we_vec2 we_window_get_size(const we_window *window) {
    if (window == NULL) {
        WE_WARN("Trying to get GLFWwindow from a NULL we_window");
        return (we_vec2){0, 0};
    }
    return (we_vec2){window->width, window->height};
}

we_bool we_window_is_closed(const we_window *window) {
    if (window == NULL) {
        WE_WARN("The we_window is NULL");
        return WE_TRUE;
    }
    return glfwWindowShouldClose(window->window);
}

void we_window_close(const we_window *window) {
    if (window == NULL) {
        WE_WARN("Trying to close a NULL we_window");
        return;
    }
    glfwSetWindowShouldClose(window->window, WE_TRUE);
}
