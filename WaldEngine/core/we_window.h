//
// Created by Toudonou on 15/03/2025.
//

#ifndef WE_WINDOW_H
#define WE_WINDOW_H

#include <GLFW/glfw3.h>

#include "core/we_defines.h"
#include "maths/we_vec2.h"

typedef struct we_window we_window;

WE_API we_window *new_we_window(const we_int8 *title, we_int32 width, we_int32 height);

WE_API void destroy_we_window(we_window **window);

WE_API void we_window_update(we_window *window);

WE_API GLFWwindow *we_window_get_glfw_window(const we_window *window);

WE_API we_vec2 we_window_get_size(const we_window *window);

WE_API we_bool we_window_is_closed(const we_window *window);

WE_API void we_window_close(const we_window *window);

#endif//WE_WINDOW_H
