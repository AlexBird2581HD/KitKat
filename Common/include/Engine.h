#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <Graphics.h>

class Engine
{
public:
	Engine();
	~Engine();
	void Update();
	void Draw();
	bool Init(int width, int height);
private:
	Graphics* graphics;
};
#endif