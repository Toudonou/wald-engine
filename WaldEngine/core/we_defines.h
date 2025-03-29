//
// Created by Toudonou on 10/03/2025.
//

#ifndef WE_DEFINE_H
#define WE_DEFINE_H

#include <stddef.h>

#define WE_API
#define WE_INLINE static

#define WE_TRUE 1
#define WE_FALSE 0

#define WE_MAX_WE_WINDOW_NAME_LENGTH 64
#define WE_MAX_WE_ENTITY_NAME_LENGTH 64
#define WE_MAX_WE_SCENE_NAME_LENGTH 64
#define WE_MAX_WE_COMPONENT_NAME_LENGTH 64

#define WE_MAX_KEYS 1024
#define WE_MAX_MOUSE_BUTTONS_KEYS 8

#define WE_PI 3.14159265358979323846
#define WE_EOF EOF

#define WE_MIN(x, y) (x < y ? x : y)
#define WE_MAX(x, y) (x > y ? x : y)

typedef unsigned char we_bool;
typedef float we_real;
typedef size_t we_size_t;

typedef char we_int8;
typedef unsigned char we_uint8;

typedef int we_int32;
typedef unsigned int we_uint32;
typedef long int we_int64;
typedef unsigned long int we_uint64;

typedef struct we_color {
    we_real r;
    we_real g;
    we_real b;
    we_real a;
} we_color;

typedef enum {
    MOUSE_LEFT = 0,
    MOUSE_RIGHT = 1,
    MOUSE_MIDDLE = 2,
    MOUSE_BUTTON_4 = 3,
    MOUSE_BUTTON_5 = 4,
    MOUSE_BUTTON_6 = 5,
    MOUSE_BUTTON_7 = 6,
    MOUSE_BUTTON_8 = 7
} we_mouse_code;

typedef enum {
    SPACE = 32,
    APOSTROPHE = 39, /* ' */
    COMMA = 44, /* , */
    MINUS = 45, /* - */
    PERIOD = 46, /* . */
    SLASH = 47, /* / */
    NUM_0 = 48,
    NUM_1 = 49,
    NUM_2 = 50,
    NUM_3 = 51,
    NUM_4 = 52,
    NUM_5 = 53,
    NUM_6 = 54,
    NUM_7 = 55,
    NUM_8 = 56,
    NUM_9 = 57,
    SEMICOLON = 59, /* ; */
    EQUAL = 61, /* = */
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,
    LEFT_BRACKET = 91, /* [ */
    BACKSLASH = 92, /* \ */
    RIGHT_BRACKET = 93, /* ] */
    GRAVE_ACCENT = 96, /* ` */
    WORLD_1 = 161, /* non-US #1 */
    WORLD_2 = 162, /* non-US #2 */

    /* Function keys */
    ESCAPE = 256,
    ENTER = 257,
    TAB = 258,
    BACKSPACE = 259,
    INSERT = 260,
    DELETE = 261,
    RIGHT = 262,
    LEFT = 263,
    DOWN = 264,
    UP = 265,
    PAGE_UP = 266,
    PAGE_DOWN = 267,
    HOME = 268,
    END = 269,
    CAPS_LOCK = 280,
    SCROLL_LOCK = 281,
    NUM_LOCK = 282,
    PRINT_SCREEN = 283,
    PAUSE = 284,
    F1 = 290,
    F2 = 291,
    F3 = 292,
    F4 = 293,
    F5 = 294,
    F6 = 295,
    F7 = 296,
    F8 = 297,
    F9 = 298,
    F10 = 299,
    F11 = 300,
    F12 = 301,
    F13 = 302,
    F14 = 303,
    F15 = 304,
    F16 = 305,
    F17 = 306,
    F18 = 307,
    F19 = 308,
    F20 = 309,
    F21 = 310,
    F22 = 311,
    F23 = 312,
    F24 = 313,
    F25 = 314,
    KP_0 = 320,
    KP_1 = 321,
    KP_2 = 322,
    KP_3 = 323,
    KP_4 = 324,
    KP_5 = 325,
    KP_6 = 326,
    KP_7 = 327,
    KP_8 = 328,
    KP_9 = 329,
    KP_DECIMAL = 330,
    KP_DIVIDE = 331,
    KP_MULTIPLY = 332,
    KP_SUBTRACT = 333,
    KP_ADD = 334,
    KP_ENTER = 335,
    KP_EQUAL = 336,
    LEFT_SHIFT = 340,
    LEFT_CONTROL = 341,
    LEFT_ALT = 342,
    LEFT_SUPER = 343,
    RIGHT_SHIFT = 344,
    RIGHT_CONTROL = 345,
    RIGHT_ALT = 346,
    RIGHT_SUPER = 347,
    MENU = 348
} we_keys_code;

#endif//WE_DEFINE_H
