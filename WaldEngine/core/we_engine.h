//
// Created by Toudonou on 15/03/2025.
//

#ifndef WE_ENGINE_H
#define WE_ENGINE_H

#include "core/we_defines.h"
#include "scene/we_scene.h"

typedef struct we_engine we_engine;

WE_API we_engine *new_we_engine(const we_int8 *title, const we_int32 width, const we_int32 height);

WE_API void destroy_we_engine(we_engine **engine);

WE_API void we_engine_update(const we_engine *engine);

WE_API void we_engine_register_we_scene(we_engine *engine, void (*start)(we_scene *scene),
                                        void (*update)(we_scene *scene));

#endif //WE_ENGINE_H
