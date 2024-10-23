/*
This script is taken from Victor Gordan on FreeCodeCamp
*/

#include "shaderClass.h"

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);
	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexCode = get_file_contents(vertexFile);
	std::string fragmentCode = get_file_contents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

    std::cout << "Compiling vertex shader..." << std::endl;
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    GLsizei maxLength = 500;
    GLchar errorLog[500];
    glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &errorLog[0]);
    std::cerr << errorLog << std::endl;

    std::cout << "Compiling fragment shader..." << std::endl;
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &errorLog[0]);
    std::cerr << errorLog << std::endl;

    std::cout << "Creating shader program..." << std::endl;
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramInfoLog(ID, maxLength, &maxLength, &errorLog[0]);
    std::cerr << errorLog << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Activate() {
    glUseProgram(ID);
}
void Shader::Delete() {
    glDeleteProgram(ID);
}