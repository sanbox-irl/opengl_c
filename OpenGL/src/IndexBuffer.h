#pragma once

typedef unsigned int u32;

class IndexBuffer {
  public:
    IndexBuffer(const void *data, u32 count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const { return m_Count; }

  private:
    u32 m_RendererID;
    u32 m_Count;
};