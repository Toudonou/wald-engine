cmake_minimum_required(VERSION 3.30)
project(WaldEngine C)

set(CMAKE_C_STANDARD 11)

#To enable compile command exports
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

include_directories(WaldEngine)

add_executable(
        ${PROJECT_NAME}
        glad/glad.c
        Sandbox/main.c
        WaldEngine/core/we_log.h
        WaldEngine/core/we_defines.h
        WaldEngine/core/we_defines.c
        WaldEngine/core/containers/we_hash_map.c
        WaldEngine/core/containers/we_hash_map.h
        WaldEngine/core/containers/we_vector.c
        WaldEngine/core/containers/we_vector.h
        WaldEngine/core/we_engine.c
        WaldEngine/core/we_engine.h
        WaldEngine/core/we_input.c
        WaldEngine/core/we_input.h
        WaldEngine/core/we_window.c
        WaldEngine/core/we_window.h
        WaldEngine/renderer/we_renderer.c
        WaldEngine/renderer/we_renderer.h
        WaldEngine/maths/we_maths.h
        WaldEngine/maths/we_vec2.c
        WaldEngine/maths/we_vec2.h
        WaldEngine/maths/we_vec3.c
        WaldEngine/maths/we_vec3.h
        WaldEngine/maths/we_vec4.c
        WaldEngine/maths/we_vec4.h
        WaldEngine/maths/we_matrix4.c
        WaldEngine/maths/we_matrix4.h
        WaldEngine/maths/we_maths_functions.c
        WaldEngine/maths/we_maths_functions.h
        WaldEngine/components/we_components.h
        WaldEngine/renderer/we_shader.c
        WaldEngine/renderer/we_shader.h
        WaldEngine/utils/we_file_utils.c
        WaldEngine/utils/we_file_utils.h
        WaldEngine/utils/we_string.c
        WaldEngine/utils/we_string.h
        WaldEngine/scene/we_entity.h
        WaldEngine/scene/we_entity.c
        WaldEngine/scene/we_scene.c
        WaldEngine/scene/we_scene.h
)

# Include GLFW and OpenGL
target_include_directories(${PROJECT_NAME} PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE GL ${GLFW_LIBRARIES} -lm)

# Link additional dependencies if needed
target_link_options(${PROJECT_NAME} PRIVATE ${GLFW_LDFLAGS})
