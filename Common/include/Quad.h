#ifndef QUAD_H
#define QUAD_H

#include <Shader.h>
#include <Texture.h>

namespace KitKat
{
	class Quad
	{
	public:
		Quad(int x, int y, int w, int h);
		~Quad();

		void move(int x, int y);
		void resize(int width, int height);
		void rotate(float angle);
		
		void setTexture(Texture* texture);
		static void setProjection(float* matrixArray);
		static float* Projection;

		void draw(Shader* shader);
	private:
		int _x, _y, _w, _h;

		Texture* _tex;

		GLuint _vbo;

		float *Translation, *Rotation, *Scale;
		float *Data;
		
		void genBuffer();
	};
}
#endif