#pragma once

#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include "utils/log.h"
#include <unordered_map>
#include "maths/glm.h"

struct ShaderSources{
    std::string Vertex;
    std::string Fragment;
};

class Shader{
protected:
    unsigned int u_ID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UnformLocation;

public:
    Shader(std::string filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;
    void SetUniform4f(std::string name, float v1, float v2, float v3, float v4);
    void SetUniform1i(std::string name, int value);
    void SetUniform1f(std::string name, float value);
    void SetUniformMat4(std::string name, glm::mat4 value);
    int GetLocation(std::string name);

    ShaderSources ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, std::string &source);
    unsigned int CreateShader(std::string &vertex_source, std::string &fragmement_source);
};
