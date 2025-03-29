//
// Created by Toudonou on 11/03/2025.
//

#ifndef WE_LOG_H
#define WE_LOG_H

#include <stdio.h>

#if _WIN32
#define WE_BREAK __debugbreak();
#elif __APPLE__
#define WE_BREAK __builtin_debugtrap();
#else
#define  WE_BREAK __builtin_trap();
#endif


#define WE_INFO(...)    printf("INFO  : "); printf(__VA_ARGS__); printf(" [%s:%s:%d]\n", __FILE__, __FUNCTION__, __LINE__);
#define WE_DEBUG(...)   printf("\033[0;32mDEBUG : "); printf(__VA_ARGS__); printf(" [%s:%s:%d]\n\033[0m", __FILE__, __FUNCTION__, __LINE__);
#define WE_WARN(...)    printf("\033[0;33mWARN  : "); printf(__VA_ARGS__); printf(" [%s:%s:%d]\n\033[0m", __FILE__, __FUNCTION__, __LINE__);
#define WE_ERROR(...)   printf("\033[0;31mERROR : "); printf(__VA_ARGS__); printf(" [%s:%s:%d]\n\033[0m", __FILE__, __FUNCTION__, __LINE__);

#define WE_ASSERT_MSG(expr, message) if(expr) {} else { printf("\033[0;31mAssertion Failure: %s, message : %s,", #expr, message); printf(" [%s:%s:%d]\n\033[0m", __FILE__, __FUNCTION__, __LINE__); WE_BREAK}


#endif //WE_LOG_H
