#include "shader.h"

GLuint createShader(const char *shaderName)
{
    char infoLog[512];

    // Get filepath of the 2 .glsl file into 2 char array
    char shaderFilepathVS[100] = "./shaders/";
    strcat(shaderFilepathVS, shaderName);
    strcat(shaderFilepathVS, "_vs.glsl");

    char shaderFilepathFS[100] = "./shaders/";
    strcat(shaderFilepathFS, shaderName);
    strcat(shaderFilepathFS, "_fs.glsl");

    // Reading Vertex shader file
    printf("Reading vertex shader file %s\n", shaderFilepathVS);
    FILE *vsFile = fopen(shaderFilepathVS, "r");
    if (vsFile == NULL)
    {
        printf("can't read shader file %s\n", shaderFilepathVS);
        return 0;
    }
    long nbrBytesVSFile = 2000; // 2ko max
    char *vsText = (char *)calloc(nbrBytesVSFile, sizeof(char));
    fread(vsText, sizeof(char), nbrBytesVSFile, vsFile);
    fclose(vsFile);

    // Reading Fragment shader file
    printf("Reading fragment shader file %s\n", shaderFilepathFS);
    FILE *fsFile = fopen(shaderFilepathFS, "r");
    if (fsFile == NULL)
    {
        printf("can't read shader file %s\n", shaderFilepathFS);
        return 0;
    }
    long nbrBytesFSFile = 2000; // 2ko max
    char *fsText = (char *)calloc(nbrBytesFSFile, sizeof(char));
    fread(fsText, sizeof(char), nbrBytesFSFile, fsFile);
    fclose(fsFile);

    // Compiling vertex shader code
    GLuint shaderVSID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderVSID, 1, &vsText, NULL);
    glCompileShader(shaderVSID);
    int success;
    glGetShaderiv(shaderVSID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderVSID, 512, NULL, infoLog);
        printf("Can't compile Vertex Shader code :\n");
        printf("%s\n", infoLog);
        free(vsText);
        free(fsText);
        return 0;
    };
    printf("Correctly compiling Vertex Shader code\n");

    // Compiling vertex shader code
    GLuint shaderFSID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderFSID, 1, &fsText, NULL);
    glCompileShader(shaderFSID);
    glGetShaderiv(shaderFSID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderFSID, 512, NULL, infoLog);
        printf("Can't compile Fragment Shader code :\n");
        printf("%s\n", infoLog);
        free(vsText);
        free(fsText);
        return 0;
    };
    printf("Correctly compiling Fragment Shader code\n");

    // Creating program
    GLuint programID = glCreateProgram();
    glAttachShader(programID, shaderVSID);
    glAttachShader(programID, shaderFSID);
    glLinkProgram(programID);
    glGetProgramiv(programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(programID, 512, NULL, infoLog);
        printf("Can't compile Shader program :\n");
        printf("%s\n", infoLog);
        free(vsText);
        free(fsText);
        return 0;
    }
    printf("Correctly compiling Shader Program\n");

    free(vsText);
    free(fsText);

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(shaderVSID);
    glDeleteShader(shaderFSID);

    return programID;
}