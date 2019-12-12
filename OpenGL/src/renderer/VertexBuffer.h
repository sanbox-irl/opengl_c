#pragma once

typedef unsigned int u32;

class VertexBuffer {
  public:
    VertexBuffer(const void *data, u32 size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

  private:
    u32 m_RendererID;
};