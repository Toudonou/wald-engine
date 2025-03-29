//
// Created by Toudonou on 15/03/2025.
//


#include <stdlib.h>
#include <string.h>
#include <GLFW/glfw3.h>

#include "core/we_input.h"
#include "core/we_log.h"

struct we_input {
    we_bool frame_keys[WE_MAX_KEYS];
    we_bool last_frame_keys[WE_MAX_KEYS];
    we_bool frame_mouse_buttons_keys[WE_MAX_MOUSE_BUTTONS_KEYS];
    we_bool last_frame_mouse_buttons_keys[WE_MAX_MOUSE_BUTTONS_KEYS];
    we_real mouse_position[2];
};

void key_callback(GLFWwindow *window, const int key, int scancode, const int action, int mods) {
    we_input *input = (we_input *) glfwGetWindowUserPointer(window);
    if (input == NULL) {
        WE_WARN("Trying to execute a key_callback on a NULL we_input");
        return;
    }
    input->frame_keys[key] = action != GLFW_RELEASE;
}

void mouse_button_callback(GLFWwindow *window, const int button, const int action, int mods) {
    we_input *input = (we_input *) glfwGetWindowUserPointer(window);
    if (input == NULL) {
        WE_WARN("Trying to execute a mouse_button_callback on a NULL we_input");
        return;
    }
    input->frame_mouse_buttons_keys[button] = action != GLFW_RELEASE;
}

void cursor_position_callback(GLFWwindow *window, const double x_pos, const double y_pos) {
    we_input *input = (we_input *) glfwGetWindowUserPointer(window);
    if (input == NULL) {
        WE_WARN("Trying to execute a cursor_position_callback on a NULL we_input");
        return;
    }
    input->mouse_position[0] = (we_real) x_pos;
    input->mouse_position[1] = (we_real) y_pos;
}

we_input *new_we_input(GLFWwindow *glfw_window) {
    WE_ASSERT_MSG(glfw_window, "the GLFWwindow must be not NULL");

    we_input *input = NULL;
    input = calloc(1, sizeof(we_input));

    if (input == NULL) {
        WE_ERROR("Error during the creation of the we_input");
        return NULL;
    }

    memset(input->frame_keys, WE_FALSE, WE_MAX_KEYS * sizeof(we_bool));
    memset(input->last_frame_keys, WE_FALSE, WE_MAX_KEYS * sizeof(we_bool));
    memset(input->frame_mouse_buttons_keys, WE_FALSE, WE_MAX_MOUSE_BUTTONS_KEYS * sizeof(we_bool));
    memset(input->last_frame_mouse_buttons_keys, WE_FALSE, WE_MAX_MOUSE_BUTTONS_KEYS * sizeof(we_bool));
    memset(input->mouse_position, 0, 2 * sizeof(we_real));

    glfwSetWindowUserPointer(glfw_window, input);

    // Setting up the callbacks
    glfwSetKeyCallback(glfw_window, key_callback);
    glfwSetMouseButtonCallback(glfw_window, mouse_button_callback);
    glfwSetCursorPosCallback(glfw_window, cursor_position_callback);

    WE_INFO("Input manager created successfully");
    return input;
}

void destroy_we_input(we_input **input) {
    if (input == NULL || *input == NULL) {
        WE_WARN("Trying to delete a NULL we_input");
        return;
    }
    free(*input);
    *input = NULL;
    WE_INFO("Input manager destroyed successfully");
}

void we_input_update(we_input *input) {
    if (input == NULL) {
        WE_WARN("Trying to update a NULL we_input")
        return;
    }

    // Copy the current frame keys to the last frame keys
    memcpy(input->last_frame_keys, input->frame_keys, WE_MAX_KEYS);

    // Copy the current frame mouse button keys to the last frame mouse button keys
    memcpy(input->last_frame_mouse_buttons_keys, input->frame_mouse_buttons_keys, WE_MAX_MOUSE_BUTTONS_KEYS);

    glfwPollEvents();
}

we_bool we_input_is_key_pressed(const we_input *input, const we_keys_code key_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(key_code < WE_MAX_KEYS, " key_code is out of bounds");
    return input->frame_keys[key_code] && !input->last_frame_keys[key_code];
}

we_bool we_input_is_key_release(const we_input *input, const we_keys_code key_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(key_code < WE_MAX_KEYS, " key_code is out of bounds");
    return !input->frame_keys[key_code] && input->last_frame_keys[key_code];
}

we_bool we_input_is_key_down(const we_input *input, const we_keys_code key_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(key_code < WE_MAX_KEYS, " key_code is out of bounds");
    return input->frame_keys[key_code];
}

we_bool we_input_is_mouse_button_pressed(const we_input *input, const we_mouse_code mouse_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(mouse_code < WE_MAX_MOUSE_BUTTONS_KEYS, "mouse_code is out of bounds");
    return input->frame_mouse_buttons_keys[mouse_code] && !input->last_frame_mouse_buttons_keys[mouse_code];
}

we_bool we_input_is_mouse_button_release(const we_input *input, const we_mouse_code mouse_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(mouse_code < WE_MAX_MOUSE_BUTTONS_KEYS, "mouse_code is out of bounds");
    return !input->frame_mouse_buttons_keys[mouse_code] && input->last_frame_mouse_buttons_keys[mouse_code];
}

we_bool we_input_is_mouse_button_down(const we_input *input, const we_mouse_code mouse_code) {
    if (input == NULL) {
        WE_WARN("Trying to get input information from a NULL we_input");
        return WE_FALSE;
    }

    WE_ASSERT_MSG(mouse_code < WE_MAX_MOUSE_BUTTONS_KEYS, "mouse_code is out of bounds");
    return input->frame_mouse_buttons_keys[mouse_code];
}
