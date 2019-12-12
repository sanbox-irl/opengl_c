#pragma once
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include <GL/glew.h>
#include <iostream>

void gl_clear_error();
bool gl_log_call(const char *function, const char *file, int line);

#define ASSERT(x)                                                                                  \
    if (!(x))                                                                                      \
        __debugbreak();

#define GLCall(x)                                                                                  \
    x;                                                                                             \
    ASSERT(gl_log_call(#x, __FILE__, __LINE__))

class Renderer {
  public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};