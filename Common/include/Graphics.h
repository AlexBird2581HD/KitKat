#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
#include <OpenGL.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <Shader.h>
#include <Quad.h>

#include <vector>

namespace KitKat
{
	class Graphics
	{
	public:
		Graphics();
		~Graphics();
		bool Init(int width, int height);
		void Draw();	
	private:
		Shader* _shader;
		GLuint gvPositionHandle;
		GLuint VBO; // Vertex Buffer Object

		//std::vector<Quad*> quads;
		Quad* quad1;
		Quad* quad2;
		Quad* quad3;

		bool setupGraphics(int w, int h);
		void clear();
		void bindVertices();
	};
}
#endif