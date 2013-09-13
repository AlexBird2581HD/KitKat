#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <OpenGL.h>

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