#pragma once
#include <GL/glew.h>

#define ASSERT(x)                                                                                  \
    if (!(x))                                                                                      \
        __debugbreak();

#define GL_CALL(x)                                                                                 \
    GLClearError();                                                                                \
    x;                                                                                             \
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))

void gl_clear_error();
bool gl_log_call(const char *function, const char *file, int line);