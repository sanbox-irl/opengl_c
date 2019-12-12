#include "Shader.h"
#include "Renderer.h"
#include "Utilities.cpp"
#include <iostream>

Shader::Shader(const std::string &vertex_shader, const std::string &fragment_shader)
    : m_VertFpath(vertex_shader), m_FragFpath(fragment_shader) {
    u32 vs = Shader::CompileShader(GL_VERTEX_SHADER, Utilities::read_file_to_string(vertex_shader));
    u32 fs =
        Shader::CompileShader(GL_FRAGMENT_SHADER, Utilities::read_file_to_string(fragment_shader));

    m_RendererID = glCreateProgram();
    glAttachShader(m_RendererID, vs);
    glAttachShader(m_RendererID, fs);
    glLinkProgram(m_RendererID);
    glValidateProgram(m_RendererID);

    glDeleteShader(vs);
    glDeleteShader(fs);
    Unbind();
}
Shader::~Shader() { glDeleteProgram(m_RendererID); }

void Shader::Bind() const { glUseProgram(m_RendererID); }
void Shader::Unbind() const { glUseProgram(0); }

// Set Uniforms
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string &name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniformMat4f(const std::string &name, const glm::mat4 &matrix) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

// Private
int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }

    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) {
        std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
    }

    m_UniformLocationCache[name] = location;

    return location;
}

u32 Shader::CompileShader(u32 type, const std::string &source) {
    u32 id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to Compile" << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                  << "Shader!" << std::endl;
        std::cout << "Filepath: " << source << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
