#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

class Graphics
{
public:
	Graphics();
	~Graphics();
	bool Init(int width, int height);
	void Draw();	
private:
	bool setupGraphics(int w, int h);
	void clear();
	void bindVertices();
	GLuint loadShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);	

	GLuint gProgram;
	GLuint gvPositionHandle;
	GLuint VBO; // Vertex Buffer Object
};

#endif