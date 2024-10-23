/*
This script is taken from Victor Gordan on FreeCodeCamp
*/

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include"VBO.h"

class VAO {
public:
	GLuint ID;
	VAO();

	void LinkVBO(VBO VBO, GLuint layout);
	void Bind();
	void UnBind();
	void Delete();
};

#endif