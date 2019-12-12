#include "Renderer.h"
#include <iostream>

void gl_clear_error() {
    while (glGetError() != GL_NO_ERROR)
        ;
}
bool gl_log_call(const char *function, const char *file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " << file << ":" << line
                  << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const { glClear(GL_COLOR_BUFFER_BIT); }

void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const {
    shader.Bind();
    va.Bind();
    ib.Bind();

    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}