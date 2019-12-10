#pragma once
#include "Renderer.h"
#include "Types.h"
#include <GL/glew.h>
#include <vector>

struct VertexBufferElement {
    u32 type;
    u32 count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(u32 type) {
        switch (type) {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout {
  public:
    VertexBufferLayout() : m_Stride(0){};

    template <typename T> void Push(u32 count) { static_assert(false); }
    template <> void Push<float>(u32 count) {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
    }
    template <> void Push<u32>(u32 count) {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
    }
    template <> void Push<char>(u32 count) {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
    }

    inline u32 GetStride() const { return m_Stride; }
    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }

  private:
    std::vector<VertexBufferElement> m_Elements;
    u32 m_Stride;
};