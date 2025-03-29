//
// Created by Toudonou on 15/03/2025.
//

#ifndef WE_INPUT_H
#define WE_INPUT_H

#include <GLFW/glfw3.h>

#include "core/we_defines.h"

typedef struct we_input we_input;

WE_API we_input *new_we_input(GLFWwindow *glfw_window);

WE_API void destroy_we_input(we_input **input);

WE_API void we_input_update(we_input *input);

WE_API we_bool we_input_is_key_pressed(const we_input *input, we_keys_code key_code);

WE_API we_bool we_input_is_key_release(const we_input *input, we_keys_code key_code);

WE_API we_bool we_input_is_key_down(const we_input *input, we_keys_code key_code);

WE_API we_bool we_input_is_mouse_button_pressed(const we_input *input, we_mouse_code mouse_code);

WE_API we_bool we_input_is_mouse_button_release(const we_input *input, we_mouse_code mouse_code);

WE_API we_bool we_input_is_mouse_button_down(const we_input *input, we_mouse_code mouse_code);

#endif//WE_INPUT_H
