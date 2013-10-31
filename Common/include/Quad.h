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

		void draw(Shader* shader);
		static float* Projection;
	private:
		int _x, _y, _w, _h;

		Texture* _tex;

		GLuint _vbo;

		float *Translation, *Rotation;
		

		void genBuffer();
	};
}
#endif