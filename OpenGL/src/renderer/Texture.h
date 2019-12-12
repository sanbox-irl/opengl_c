#pragma once

#include "Renderer.h"
#include "Types.h"

class Texture {
  public:
    Texture(const std::string &filepath);
    ~Texture();

    void Bind(u32 slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }

  private:
    u32 m_RendererID;
    std::string m_FilePath;
    unsigned char *m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
};