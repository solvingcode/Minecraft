#include "shader.h"

Shader::Shader(std::string filepath): m_Filepath(filepath){
    ShaderSources shaders = ParseShader(filepath);
    u_ID = CreateShader(shaders.Vertex, shaders.Fragment);
}

ShaderSources Shader::ParseShader(const std::string &filepath){

    std::ifstream stream(filepath);

    enum ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            }else if(line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }else{
            ss[(int)type] << line << "\n";
        }
    }

    return {
        ss[(int)ShaderType::VERTEX].str(),
        ss[(int)ShaderType::FRAGMENT].str()
    };
}

unsigned int Shader::CompileShader(unsigned int type, std::string &source){
    unsigned int id = glCreateShader(type);
    const char * sourceStr = source.c_str();
    CallGL(glShaderSource(id, 1, &sourceStr, nullptr));
    CallGL(glCompileShader(id));

    int result;
    CallGL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE){
        int length;
        CallGL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char msg[length];
        CallGL(glGetShaderInfoLog(id, length, &length, msg));
        std::cout << "Failed to compile shader " << (type == GL_VERTEX_SHADER ? "vertex" : "fragmenet") << std::endl;
        std::cout << msg << std::endl;
        CallGL(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::CreateShader(std::string &vertex_source, std::string &fragmement_source){
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_source);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmement_source);

    CallGL(glAttachShader(program, vs));
    CallGL(glAttachShader(program, fs));

    CallGL(glLinkProgram(program));
    CallGL(glValidateProgram(program));

    CallGL(glDeleteShader(vs));
    CallGL(glDeleteShader(fs));

    return program;
}

void Shader::Bind() const{
    CallGL(glUseProgram(u_ID));
}

void Shader::Unbind() const{
    CallGL(glUseProgram(0));
}

int Shader::GetLocation(std::string name){
    if(m_UnformLocation.find(name) != m_UnformLocation.end()){
        return m_UnformLocation[name];
    }
    CallGL(int location = glGetUniformLocation(u_ID, name.c_str()));
    if(location == -1){
        std::cout << "Warning : Location of " << name << " not founded !" << std::endl; 
    }
    m_UnformLocation[name] = location;
    return location;
}

void Shader::SetUniform4f(std::string name, float v1, float v2, float v3, float v4){
    int location = GetLocation(name);
    if(location != -1){
        CallGL(glUniform4f(location,v1, v2, v3, v4));
    }
}

void Shader::SetUniform1i(std::string name, int value){
    int location = GetLocation(name);
    CallGL(glUniform1i(location,value));
}

void Shader::SetUniform1f(std::string name, float value){
    int location = GetLocation(name);
    CallGL(glUniform1f(location,value));
}

void Shader::SetUniformMat4(std::string name, glm::mat4 value){
    int location = GetLocation(name);
    CallGL(glUniformMatrix4fv(location, 1, GL_FALSE, (const float *)&value));
}

Shader::~Shader(){
    LogTrace("Destructing Shader %d...\n", u_ID);
    glDeleteProgram(u_ID);
}
