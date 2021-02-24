#include "shader.h"

Shader::Shader()
{
    sharerID = 0;
    uniformProjection = 0;
    uniformModel = 0;
}

Shader::~Shader() { clearShader(); }

void Shader::createFromString(const char *vertexCode, const char *fragmentCode) { compileShader(vertexCode, fragmentCode); }

void Shader::createFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
    std::string vertexString = readFile(vertexLocation);
    std::string fragmentString = readFile(fragmentLocation);
    const char *vertexCode = vertexString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}

std::string Shader::readFile(const char *fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if (!fileStream.is_open())
    {
        printf("Failed to read %s! File doesn't exist.", fileLocation);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

GLuint Shader::getProjectionLocation() { return uniformProjection; }

GLuint Shader::getModelLocation() { return uniformModel; }

void Shader::useShader() { glUseProgram(sharerID); }

void Shader::clearShader()
{

    if (0 != sharerID)
    {
        glDeleteProgram(sharerID);
        sharerID = 0;
    }
    uniformModel = 0;
    uniformProjection = 0;
}

void Shader::compileShader(const char *vertexCode, const char *fragmentCode)
{
    sharerID = glCreateProgram();

    if (!sharerID)
    {
        printf("Failed to create shader\n");
        return;
    }

    addShader(sharerID, vertexCode, GL_VERTEX_SHADER);
    addShader(sharerID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(sharerID);
    glGetProgramiv(sharerID, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(sharerID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    glValidateProgram(sharerID);
    glGetProgramiv(sharerID, GL_VALIDATE_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(sharerID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    uniformModel = glGetUniformLocation(sharerID, "model");
    uniformProjection = glGetUniformLocation(sharerID, "projection");
}

void Shader::addShader(GLuint theProgram, const char *shaderCode, GLenum shaderType)
{

    GLuint theShader = glCreateShader(shaderType);

    const GLchar *theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(theShader, 1024, NULL, eLog);
        fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}
