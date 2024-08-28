#include <renderer/shader.h>

shader_t::shader_t(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    fs::path p = fs::current_path();

    std::cout << p << std::endl;

    std::string vertFullPath = p.string() + vertexPath;
    std::string fragFullPath = p.string() + fragmentPath;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vShaderFile.open(vertFullPath);
        fShaderFile.open(fragFullPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << '\n';
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    rendererID_ = glCreateProgram();
    glAttachShader(rendererID_, vertex);
    glAttachShader(rendererID_, fragment);
    glLinkProgram(rendererID_);

    glGetProgramiv(rendererID_, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(rendererID_, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void shader_t::Bind()
{
    glUseProgram(rendererID_);
}

void shader_t::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(rendererID_, name.c_str()), (int)value);
}

void shader_t::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(rendererID_, name.c_str()), value);
}

void shader_t::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(rendererID_, name.c_str()), value);
}

void shader_t::SetVec3(const std::string &name, glm::vec3 value) const
{
    // Note: Probably should check that the location is not -1 in all of these methods
    glUniform3fv(glGetUniformLocation(rendererID_, name.c_str()), 1, glm::value_ptr(value));
}

void shader_t::SetVec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(rendererID_, name.c_str()), x, y, z);
}

void shader_t::SetMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(rendererID_, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
