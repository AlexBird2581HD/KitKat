#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#ifdef WINDOWS_FRAMEWORK
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
private:
	void clear();

	//Debug
	static void checkGlError(const char* op);
};
#endif