/*******************************************************************
**   File: opengl.h
** Author:	Paul Allen
**
** The opengl library provides a cross platform framework for
** a graphical windowed program environment. Its main purpose 
** is to be used in Software Engineering classes at FGCU. The
** library is based on code presented by LearnOpenGL.com.
******************************************************************/
#ifndef OPENGL_H
#define OPENGL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class OpenGL {
public:
	OpenGL(){}
	OpenGL(int width, int height, const char* title, bool borders=false, int margin=0);
	~OpenGL() { glfwTerminate(); }

	bool isClosing() { return glfwWindowShouldClose(this->window); };

	void clearWindow();
	void clearWindow(float red, float green, float blue);
	void clearWindow(std::vector<float> background);
	void paintWindow();

	void DrawSprite(float position_x, float position_y, float size_x, float size_y, int color_r, int color_g, int color_b);
		
	void DrawSprite(float position_x, float position_y, float size_x, float size_y, float rotate,
		int color_r, int color_g, int color_b);
		
	void DrawSprite(float position_x, float position_y, float size_x, float size_y, float rotate = 0.0f,
		float color_r = 1.0f, float color_g = 1.0f, float color_b = 1.0f);

	void DrawSprite(std::vector<float> position, std::vector<float> size, float rotate = 0.0f,
		std::vector<float> color = {1.0f, 1.0f, 1.0f});

private:
	GLFWwindow* window;
	unsigned int shaderProgram;
	unsigned int renderData;

};

#endif OPENGL_H