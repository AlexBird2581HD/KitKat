#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

class Engine
{
public:
	Engine();
	~Engine();
	void Update();
	void Draw();
	void Init(int w, int h);
private:
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);
	bool setupGraphics(int w, int h);
	void clear();

	GLuint gProgram;
	GLuint gvPositionHandle;
};
#endif