#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <Shader.h>
#include <Quad.h>

namespace KitKat
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		bool Init(int width, int height);
		void Update();
		void Draw();		
	private:
		int screenWidth, screenHeight;

		Shader* shader;

		Quad* quad1;
		Quad* quad2;
		Quad* quad3;

		bool setupGraphics(int width, int height);
	};
}
#endif