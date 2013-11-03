#pragma once
#ifndef ENGINE
#define ENGINE

#include <Win32toAndroid.h>

class Shader;
class Quad;

class Engine
{
public:

	Engine();
	~Engine(); 
	void fixAspectRatio(float desiredWidth,float desiredHeight,float width,float height);
	void Update();
	void Draw();
	float Scale,blackBarH,blackBarV;
	int x,y;

	private:

		int width, height;
	
		GLfloat* GlProjection;

		float sine;

		Quad* Quad1;
		Quad* Quad2;
		Quad* Quad3;

		int velx, vely;

		GLuint Texture;
};
#endif
