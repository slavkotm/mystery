#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/gl.h>

class Shader
{

public:
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void use() { glUseProgram(this->program); } 

private:
	GLint program;	
};

#endif /* _SHADER_H_ */
