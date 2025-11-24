#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const std::string& vertexShaderFilePath,
           const std::string& fragmentShaderFilePath);

    ~Shader();

    void Bind() const;
    void Unbind() const;

    // uniforms
    void setUniform1i(const std::string& name, int value) const;
    void setUniform1f(const std::string& name, float value) const;
    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const;
    void setUniform3fv(const std::string& name, const glm::vec3& vector) const;
    void setUniformMat4f(const std::string& name, const glm::mat4& matrix) const;

private:
    GLuint LoadShaders(const std::string& vertex_file_path,
                       const std::string& fragment_file_path);

    GLuint m_RendererID;

    GLuint GetUniformLocation(const std::string& name) const;
    mutable std::unordered_map<std::string, int> m_UniformLocationCache;
};

#endif
