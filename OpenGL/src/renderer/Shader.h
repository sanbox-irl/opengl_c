#pragma once
#include "Types.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

class Shader {
  public:
    Shader(const std::string &vertex_shader, const std::string &fragment_shader);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    // Set Uniforms
    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);
    void SetUniform1i(const std::string &name, int value);
    void SetUniformMat4f(const std::string &name, const glm::mat4 &matrix);

  private:
    std::string m_VertFpath;
    std::string m_FragFpath;
    u32 m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

    u32 CompileShader(u32 type, const std::string &source);
    int GetUniformLocation(const std::string &name);
};