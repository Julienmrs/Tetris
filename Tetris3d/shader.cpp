#include "shader.h"

Shader::Shader(const std::string& vertexShaderFilePath,
               const std::string& fragmentShaderFilePath)
    : m_RendererID(0)
{
    m_RendererID = LoadShaders(vertexShaderFilePath, fragmentShaderFilePath);
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
}

GLuint Shader::LoadShaders(const std::string& vertex_file_path,
                           const std::string& fragment_file_path)
{
    // --- Load files ---
    std::ifstream vFile(vertex_file_path);
    std::ifstream fFile(fragment_file_path);

    if (!vFile.is_open()) {
        std::cerr << "[SHADER] ERREUR : impossible d'ouvrir " << vertex_file_path << std::endl;
        return 0;
    }
    if (!fFile.is_open()) {
        std::cerr << "[SHADER] ERREUR : impossible d'ouvrir " << fragment_file_path << std::endl;
        return 0;
    }

    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();

    std::string vertexCode = vStream.str();
    std::string fragmentCode = fStream.str();


    if (vertexCode.empty() || fragmentCode.empty()) {
        std::cerr << "[SHADER] ERREUR : fichier shader vide !\n";
        return 0;
    }

    //  Shaders
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vsSrc = vertexCode.c_str();
    glShaderSource(vs, 1, &vsSrc, nullptr);
    glCompileShader(vs);

    GLint ok;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len;
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(vs, len, nullptr, log.data());
        std::cerr << "[SHADER] ERREUR compilation VS:\n" << log.data() << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fsSrc = fragmentCode.c_str();
    glShaderSource(fs, 1, &fsSrc, nullptr);
    glCompileShader(fs);

    glGetShaderiv(fs, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint len;
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetShaderInfoLog(fs, len, nullptr, log.data());
        std::cerr << "[SHADER] ERREUR compilation FS:\n" << log.data() << std::endl;
    }

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint len;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
        std::vector<char> log(len);
        glGetProgramInfoLog(prog, len, nullptr, log.data());
        std::cerr << "[SHADER] ERREUR link program:\n" << log.data() << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);

    return prog;
}

void Shader::Bind() const {
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

GLuint Shader::GetUniformLocation(const std::string& name) const
{
    if (m_UniformLocationCache.contains(name))
        return m_UniformLocationCache.at(name);

    int loc = glGetUniformLocation(m_RendererID, name.c_str());
    if (loc == -1)
        std::cout << "WARNING: uniform '" << name << "' not found.\n";

    m_UniformLocationCache[name] = loc;
    return loc;
}

void Shader::setUniform1i(const std::string& name, int value) const {
    glUniform1i(GetUniformLocation(name), value);
}
void Shader::setUniform1f(const std::string& name, float value) const {
    glUniform1f(GetUniformLocation(name), value);
}
void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) const {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::setUniform3fv(const std::string& name, const glm::vec3& vector) const {
    glUniform3fv(GetUniformLocation(name), 1, &vector[0]);
}
void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) const {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}
